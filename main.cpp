#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <limits>

#include <Windows.h>
#include <WinUser.h>

#include "data_structures.h"
#include "class_Position2DVector.h"
#include "class_Player.h"
#include "class_Display.h"

// General comments
// Const not used enough
// What is the difference between
// 1. const bool myFunction()
// 2. bool myFunction() const

// noexcept not used enough
// what is the point of noexcept

int main()
{
    // Initialize variables ////////////////////////////////////////////////

    // Create display object
    Display display;

    // Create player object & playerBullets object
    Player player;
    Position2DVector playerBullets;

    // Create enemies object & enemyBullets object
    Position2DVector enemies{{1,2}, {2,3}, {1,2}}; 
    Position2DVector enemyBullets;

    // Initialize random number generator
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distribution(1, 100);

    // What is a reasanable lenght of a method?

    // init Display
    // Init Game
    // is everything ready?
    // while(1)
        // is game over?
        // Turn
        // update game state
        // display




    // Initialize keyboard input variables
    bool bKeyLeft = FALSE;
    bool bKeyRight = FALSE;
    bool bKeyLeftOld = FALSE;
    bool bKeyRightOld = FALSE;
    bool bKeySpace = FALSE;
    bool bKeySpaceOld = FALSE;
    std::chrono::milliseconds timeDelay(100);

    // Set Enemy initial positions
    enemies.addPos(15, 15);
    enemies.addPos(14, 14);
    enemies.addPos(16, 14);
    enemies.addPos(15, 13);
    enemies.addPos(13, 13);
    enemies.addPos(17, 13);

    enemies.addPos(25, 15);
    enemies.addPos(24, 14);
    enemies.addPos(26, 14);
    enemies.addPos(25, 13);
    enemies.addPos(23, 13);
    enemies.addPos(27, 13);

    enemies.addPos(35, 15);
    enemies.addPos(34, 14);
    enemies.addPos(36, 14);
    enemies.addPos(35, 13);
    enemies.addPos(33, 13);
    enemies.addPos(37, 13);

    // Set Enemy initial movement direction
    enum MovementDirection enemyMovementDirection = MOVE_LEFT;

    // Game Loop
    
    while (TRUE)
    {
        // Get Player Input
        auto startTime = std::chrono::system_clock::now();
        while ((std::chrono::system_clock::now() - startTime) < timeDelay)
        {
            // Can we have nicer way to get what key was pressed?
            bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
            bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;
            bKeySpace = (0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) != 0;

            if (bKeyRight && !bKeyRightOld)
            {
                player.setPosition(MOVE_RIGHT);
            }
            if (bKeyLeft && !bKeyLeftOld)
            {
                player.setPosition(MOVE_LEFT);
            }

            if (bKeySpace && !bKeySpaceOld)
            {
                playerBullets.addPos(player.getPosition());
            }

            bKeyRightOld = bKeyRight;
            bKeyLeftOld = bKeyLeft;
            bKeySpaceOld = bKeySpace;
        }

        // Game Logic //////////////////////////////////////////////////////////
        // Why is all of game logic in main?

        // Local variables
        Position2D temp{}; // why does temp exist?
        Position2D borderEnemy{};

        // Move Player Bullets
        for (size_t i = 0; i < playerBullets.getVectorSize(); i++)
        {
            temp = playerBullets.getPos(i);
            if (temp.y <= 4)
            {
                playerBullets.removePos(temp);
            }
            else
            {
                playerBullets.updatePos(i, MOVE_UP);
            }
        }

        // Spawn Enemy Bullets
        for (size_t i = 0; i < enemies.getVectorSize(); i++)
        {
            temp = enemies.getPos(i);
            int random_number = distribution(generator);
            if (random_number <= 1) 
            {
                enemyBullets.addPos(temp);
            }
        }

        // Move Enemy Bullets
        for (size_t i = 0; i < enemyBullets.getVectorSize(); i++)
        {
            temp = enemyBullets.getPos(i);
            if (temp.y >= SCREEN_HEIGHT - 2)
            {
                enemyBullets.removePos(temp);
            }
            else
            {
                enemyBullets.updatePos(i, MOVE_DOWN);
            }
        }

        // Move Enemies
        switch (enemyMovementDirection)
        {
            case MOVE_LEFT:
                // Search for the most LEFT enemy position
                for (size_t i = 0; i < enemies.getVectorSize(); i++)
                {
                    temp = enemies.getPos(i);
                    if (i == 0)
                    {
                        borderEnemy = enemies.getPos(i);
                    }
                    else
                    {
                        if (temp.x < borderEnemy.x)
                        {
                            borderEnemy = temp;
                        }
                    }
                }
                // Move LEFT if NOT at screen border, else change direction
                if (borderEnemy.x > 1)
                {
                    for (size_t i = 0; i < enemies.getVectorSize(); i++)
                    {
                        enemies.updatePos(i, MOVE_LEFT);
                    }
                }
                else 
                {
                    enemyMovementDirection = MOVE_RIGHT;
                    for (size_t i = 0; i < enemies.getVectorSize(); i++)
                    {
                        enemies.updatePos(i, MOVE_RIGHT);
                        enemies.updatePos(i, MOVE_DOWN);
                    }
                }
                break;

            case MOVE_RIGHT:
                // Search for the most RIGHT enemy position
                for (size_t i = 0; i < enemies.getVectorSize(); i++)
                {
                    temp = enemies.getPos(i);
                    if (i == 0)
                    {
                        borderEnemy = enemies.getPos(i);
                    }
                    else
                    {
                        if (temp.x > borderEnemy.x)
                        {
                            borderEnemy = temp;
                        }
                    }
                }
                // Move RIGHT if NOT at screen border, else change direction
                if (borderEnemy.x < SCREEN_WIDTH - 2)
                {
                    for (size_t i = 0; i < enemies.getVectorSize(); i++)
                    {
                        enemies.updatePos(i, MOVE_RIGHT);
                    }
                }
                else
                {
                    enemyMovementDirection = MOVE_LEFT;
                    for (size_t i = 0; i < enemies.getVectorSize(); i++)
                    {
                        enemies.updatePos(i, MOVE_LEFT);
                        enemies.updatePos(i, MOVE_DOWN);
                    }
                }
                break;
        }
        
        // Player Bullet collision dinamics
        for (size_t i = 0; i < playerBullets.getVectorSize(); i++) 
        {
            temp = playerBullets.getPos(i);
            if (enemies.isContaining(temp))
            {
                playerBullets.removePos(temp);
                enemies.removePos(temp);
                player.updateScore(10);
            }
        }

        // Enemy Bullet collision dinamics
        if (enemyBullets.isContaining(player.getPosition()))
        {
            enemyBullets.removePos(player.getPosition());
            player.updateLives(-1);
        }

        // Display /////////////////////////////////////////////////////////////
        
        // Clear Screen
        display.clearScreen();

        // Update Border & Interface
        display.updateGameBorder();
        display.updatePlayerInterface(player);

        // Draw Player Ship
        display.updatePosition(player.getPosition(), L'W');

        // Draw Player Bullets
        display.updatePositionVector(playerBullets, L'.');

        // Draw Enemy Bullets
        display.updatePositionVector(enemyBullets, L'�');

        // Draw Enemies
        display.updatePositionVector(enemies, L'Y');
        
        // Display Frame
        display.updateFrame();
    }
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
