#ifndef DISPLAY_H
#define DISPLAY_H

#include <Windows.h>
#include <WinUser.h>

#include "class_Player.h"

class Display
{
private:
    wchar_t* screen;
    HANDLE hConsole;
    DWORD dwBytesWritten;

public:
    // Constructor
    Display();

    // Destructor
    ~Display();

    // Draw Game Border
    void drawGameBorder();

    // Draw Player Interface
    void drawPlayerInterface(Player& player);

    // Draw character to a position
    void drawCharToPosition(const Position2D& position, const wchar_t wc);

    void drawCharToPosition(int x, int y, const wchar_t wc);

    // Draw character to all positions in a vector
    void drawCharToPositionsInVector(Position2DVector& posVec, const wchar_t wc);

    // Draw Frame
    void drawFrame();

};

#endif
