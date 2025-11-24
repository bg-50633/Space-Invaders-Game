#include "class_Display.h"


// Constructor
Display::Display() : screen{std::make_unique(13213)}
{
    // using new is code smell
    // why wchar_t?
    screen = new wchar_t[SCREEN_WIDTH * SCREEN_HEIGHT]
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    dwBytesWritten = 0;
}

// Destructor
Display::~Display() {

    // delete? or maybe screen needs to be something else?
};

// Clear Screen
void Display::clearScreen()
{
    // Not readable, this isn't part of really any style
    // Must use curly braces
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';
}

// Draw Game Border
void Display::updateGameBorder()
{
    // why not part of clear screen
    // How can we optize, current O(n^2)
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            if ((j == 0) || (j == SCREEN_HEIGHT - 1))
            {
                // How can we make "i * SCREEN_WIDTH + j" more friendly/readable, pixelAt(1,2) = L'|'
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
    // we can user std::format
    wsprintf(&screen[SCREEN_WIDTH + 1], L"Player: %ws", player.getName());
    wsprintf(&screen[SCREEN_WIDTH + SCREEN_WIDTH - 15], L"Score: %d", player.getScore());
    wsprintf(&screen[2 * SCREEN_WIDTH + 1], L"Lives: %d", player.getLives());
}

// Draw character to a position
void Display::updatePosition(const Position2D& position, const wchar_t wc)
{
    // What does updatePosition do for display class? Is there a better name for this?
    screen[position.y * SCREEN_WIDTH + position.x] = wc;
}

// Draw character to all positions in a vector
void Display::updatePositionVector(Position2DVector& posVec, const wchar_t wc)
{
    // Why do we need this check?
    if (!(posVec.isEmpty()))
    {
        // Is there a nicer way to iterate? (yes) What do we need to achieve it?
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
