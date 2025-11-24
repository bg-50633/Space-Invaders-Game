#ifndef DISPLAY_H
#define DISPLAY_H

#include <Windows.h>
#include <WinUser.h>

#include "class_Player.h"

// Should this be called Display if it sepecialized for the game?
class Display
{
private:
    // what else can we use instead of raw pointer
    // Smart pointer? unique_ptr, shared_ptr?   
    wchar_t* screen;
    HANDLE hConsole;
    DWORD dwBytesWritten;

public:
    // Constructor
    // Why doesn't display get constructed with dimensions?
    // What if I want display of 100x200?
    // Rule of 3, 5?
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