#include "class_Display.h"


// Constructor
Display::Display()
{
    screen = new wchar_t[SCREEN_WIDTH * SCREEN_HEIGHT];
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    dwBytesWritten = 0;
}

// Destructor
Display::~Display() {};

// Clear Screen
void Display::clearScreen()
{
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';
}

// Draw Game Border
void Display::updateGameBorder()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            if ((j == 0) || (j == SCREEN_HEIGHT - 1))
            {
                screen[i * SCREEN_WIDTH + j] = L'|';
            }
            else if ((i == 0) || (i == 3))
            {
                screen[i * SCREEN_WIDTH + j] = L'#';
            }
            else if ((i == SCREEN_WIDTH - 1))
            {
                screen[i * SCREEN_WIDTH + j] = L'_';
            }
        }
    }
}

// Draw Player Interface
void Display::updatePlayerInterface(Player& player)
{

    wsprintf(&screen[SCREEN_WIDTH + 1], L"Player: %ws", player.getName());
    wsprintf(&screen[SCREEN_WIDTH + SCREEN_WIDTH - 15], L"Score: %d", player.getScore());
    wsprintf(&screen[2 * SCREEN_WIDTH + 1], L"Lives: %d", player.getLives());
}

// Draw character to a position
void Display::updatePosition(const Position2D& position, const wchar_t wc)
{
    screen[position.y * SCREEN_WIDTH + position.x] = wc;
}

// Draw character to all positions in a vector
void Display::updatePositionVector(Position2DVector& posVec, const wchar_t wc)
{
    if (!(posVec.isEmpty()))
    {
        for (size_t i = 0; i < posVec.getVectorSize(); i++)
        {
            screen[posVec.getPos(i).y * SCREEN_WIDTH + posVec.getPos(i).x] = wc;
        }
    }
}

// Update Frame
void Display::updateFrame()
{
    WriteConsoleOutputCharacter(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0,0 }, &dwBytesWritten);
}
