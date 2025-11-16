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

    // Clear Screen
    void clearScreen();

    // Draw Game Border
    void updateGameBorder();

    // Draw Player Interface
    void updatePlayerInterface(Player& player);

    // Draw character to a position
    void updatePosition(const Position2D& position, const wchar_t wc);

    // Draw character to all positions in a vector
    void updatePositionVector(Position2DVector& posVec, const wchar_t wc);

    // Update Frame
    void updateFrame();

};

#endif