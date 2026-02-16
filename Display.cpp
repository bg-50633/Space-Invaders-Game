#include "Display.h"


// Constructor
Display::Display(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    screen = std::make_unique<wchar_t[]>(static_cast<size_t>(width) * static_cast<size_t>(height));
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    dwBytesWritten = 0;
}

// Destructor
Display::~Display() {};

// Draw Game Border
void Display::drawGameBorder()
{
    for (int i = 0; i < screenWidth; i++)
    {
        for (int j = 0; j < screenHeight; j++)
        {
            if ((j == 0) || (j == screenHeight - 1))
            {
                drawCharToPosition(j, i, L'|');
            }
            else if ((i == 0) || (i == 3))
            {
                drawCharToPosition(j, i, L'#');
            }
            else if ((i == screenWidth - 1))
            {
                drawCharToPosition(j, i, L'_');
            }
            else
            {
                drawCharToPosition(j, i, L' ');
            }
        }
    }
}

// Draw Player Interface
void Display::drawPlayerInterface(const Player& player)
{
    std::wstring score = std::to_wstring(player.score);
    std::wstring lives = std::to_wstring(player.lives);

    // Write player name
    writeString(L"Player: ", screenWidth + 1);
    writeString(player.name.c_str(), screenWidth + 9);

    // Write player score
    writeString(L"Score: ", 2 * screenWidth - 15);
    writeString(score.c_str(), 2 * screenWidth - 8);

    // Write player lives
    writeString(L"Lives: ", 2 * screenWidth + 1);
    writeString(lives.c_str(), 2 * screenWidth + 8);
}

// Draw character to a position
void Display::drawCharToPosition(const Position2D& position, const wchar_t wc)
{
    screen[position.y * screenWidth + position.x] = wc;
}

// Draw character to a position from coordinates
void Display::drawCharToPosition(int x, int y, const wchar_t wc)
{
    screen[y * screenWidth + x] = wc;
}

// Draw character to all positions in a vector
void Display::drawCharToPositionsInVector(Position2DVector& posVec, const wchar_t wc)
{
    for (Position2D pos : posVec.getPosVec())
    {
        drawCharToPosition(pos, wc);
    }
}

// Get display screen pointer value
const wchar_t* Display::getScreenRawPointer()
{
    return screen.get();
}

// Prompt and read player name from console input
std::wstring Display::promptPlayerName()
{
    std::wstring playerName;
    wchar_t wch = 0;
    size_t cnt = 0;

    writeString(L"=================================================", 0);
    writeString(L"=================================================", screenWidth);
    writeString(L"#           _____                               #", screenWidth * 2);
    writeString(L"#          / ____|                              #", screenWidth * 3);
    writeString(L"#         | (___  _ __   __ _  ___ ___          #", screenWidth * 4);
    writeString(L"#          \\___ \\| '_ \\ / _` |/ __/ _ \\         #", screenWidth * 5);
    writeString(L"#          ____) | |_) | (_| | (_|  __/         #", screenWidth * 6);
    writeString(L"#         |_____/| .__/ \\__,_|\\___\\___|         #", screenWidth * 7);
    writeString(L"#                | |                            #", screenWidth * 8);
    writeString(L"#                |_|                            #", screenWidth * 9);
    writeString(L"=================================================", screenWidth * 10);
    writeString(L"=================================================", screenWidth * 11);
    writeString(L"#   _____                     _                 #", screenWidth * 12);
    writeString(L"#  |_   _|                   | |                #", screenWidth * 13);
    writeString(L"#    | |  _ ____   ____ _  __| | ___ _ __ ___   #", screenWidth * 14);
    writeString(L"#    | | | '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|  #", screenWidth * 15);
    writeString(L"#   _| |_| | | \\ V / (_| | (_| |  __/ |  \\__ \\  #", screenWidth * 16);
    writeString(L"#  |_____|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/  #", screenWidth * 17);
    writeString(L"=================================================", screenWidth * 18);
    writeString(L"=================================================", screenWidth * 19);

    writeString(L"Player Name (Press Enter to confirm): ", screenWidth * 21);
    updateFrame();

    while ((wch = _getwch()) != '\r')
    {
        if (wch == '\b')
        {
            if (!playerName.empty())
            {
                playerName.pop_back();
                cnt--;
                writeString(L" ", screenWidth * 22 + cnt);
            }
        }
        else
        {
            playerName += wch;
            writeString(playerName.c_str(), screenWidth * 22);
            cnt++;
        }
        updateFrame();
    }
    return playerName;
}

// Write a string to the screen starting from a specified index
void Display::writeString(const wchar_t* str, size_t startIndex)
{
    size_t strLength = std::wcslen(str);
    if (startIndex + strLength < screenWidth * screenHeight)
    {
        std::copy(str, str + strLength, screen.get() + startIndex);
    }
}

// Write game state message
void Display::writeGameStateMessage(const GameState& gameState)
{
    switch (gameState)
    {
    case (GAME_IN_PROGRESS):
        break; 

    case (PLAYER_WON):
        writeString(L"YOU WIN!", screenWidth * 5 + 21);
        writeString(L"(Press Enter to Exit)", screenWidth * 6 + 15);
        updateFrame();
        break;

    case (PLAYER_HAS_ZERO_LIVES):
        writeString(L"GAME OVER", screenWidth * 5 + 21);
        writeString(L"You lost all lives", screenWidth * 6 + 17);
        writeString(L"(Press Enter to Exit)", screenWidth * 7 + 15);
        updateFrame();
        break;

    case (ENEMIES_REACHED_PLAYER):
        writeString(L"GAME OVER", screenWidth * 5 + 21);
        writeString(L"Enemies broke through", screenWidth * 6 + 15);
        writeString(L"(Press Enter to Exit)", screenWidth * 7 + 15);
        updateFrame();
        break;
    }
}

// Draw Frame
void Display::updateFrame()
{
    WriteConsoleOutputCharacter(hConsole, getScreenRawPointer(), screenWidth * screenHeight, {0,0}, &dwBytesWritten);
}
