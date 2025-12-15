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

// Draw Game Border
void Display::drawGameBorder()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            if ((j == 0) || (j == SCREEN_HEIGHT - 1))
            {
                drawCharToPosition(j, i, L'|');
            }
            else if ((i == 0) || (i == 3))
            {
                drawCharToPosition(j, i, L'#');
            }
            else if ((i == SCREEN_WIDTH - 1))
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
void Display::drawPlayerInterface(Player& player)
{
    wsprintf(&screen[SCREEN_WIDTH + 1], L"Player:");
    wsprintf(&screen[SCREEN_WIDTH + SCREEN_WIDTH - 15], L"Score: %d", player.getScore());
    wsprintf(&screen[2 * SCREEN_WIDTH + 1], L"Lives: %d", player.getLives());
}

// Draw character to a position
void Display::drawCharToPosition(const Position2D& position, const wchar_t wc)
{
    screen[position.y * SCREEN_WIDTH + position.x] = wc;
}

void Display::drawCharToPosition(int x, int y, const wchar_t wc)
{
    screen[y * SCREEN_WIDTH + x] = wc;
}

// Draw character to all positions in a vector
void Display::drawCharToPositionsInVector(Position2DVector& posVec, const wchar_t wc)
{
    for (Position2D pos : posVec.getPosVec())
    {
        drawCharToPosition(pos, wc);
    }
}

// Draw Frame
void Display::drawFrame()
{
    WriteConsoleOutputCharacter(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0,0 }, &dwBytesWritten);
}
