#ifndef DISPLAY_H
#define DISPLAY_H

#include <Windows.h>
#include <conio.h>
#include <cwchar>

#include "data_structures.h"
#include "Position2DVector.h"

class Display
{
private:
    int screenWidth;
    int screenHeight;
    std::unique_ptr<wchar_t[]> screen;
    HANDLE hConsole;
    DWORD dwBytesWritten;

public:
    // Constructor
    Display(int width, int height);

    // Destructor
    ~Display();

    // Draw Game Border
    void drawGameBorder();

    // Draw Player Interface
    void drawPlayerInterface(const Player& player);

    // Draw character to a position
    void drawCharToPosition(const Position2D& position, const wchar_t wc);

    // Draw character to a position from coordinates
    void drawCharToPosition(int x, int y, const wchar_t wc);

    // Draw character to all positions in a vector
    void drawCharToPositionsInVector(Position2DVector& posVec, const wchar_t wc);

    // Prompt and read player name from console input
    std::wstring promptPlayerName();

    // Get display screen pointer value
    const wchar_t* getScreenRawPointer();

    // Write a string to the screen starting from a specified index
    void writeString(const wchar_t* str, size_t startIndex = 0);

    // Write game state message
    void writeGameStateMessage(const GameState& gameState);

    // Draw Frame
    void updateFrame();

};

#endif