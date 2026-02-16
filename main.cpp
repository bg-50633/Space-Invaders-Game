#include "Display.h"
#include "GameLogic.h"

constexpr auto SCREEN_WIDTH = 50;
constexpr auto SCREEN_HEIGHT = 50;

int main()
{
    //////////////////////////////////////////////////////////////////////
    // Initialization
    //////////////////////////////////////////////////////////////////////

    // Create display object
    Display display(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Create GameLogic object
    GameLogic gameLogic(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialize player
    gameLogic.playerInit();

    // Set player name from input
    gameLogic.playerSetName(display.promptPlayerName());

    // Set Enemy initial positions & movement direction
    gameLogic.enemyVecInit();

    // Initialize random number generator
    gameLogic.randomGeneratorInit();

    //////////////////////////////////////////////////////////////////////
    // Game Loop
    //////////////////////////////////////////////////////////////////////
    
    while (TRUE)
    {
        // Get Player Keyboard Input
        gameLogic.getKeyboardInput();

        // Move Player Bullets
        gameLogic.pBulletsMove();

        // Spawn Enemy Bullets
        gameLogic.eBulletsSpawn();

        // Move Enemy Bullets
        gameLogic.eBulletsMove();

        // Move Enemies
        gameLogic.enemyVecMove();
        
        // Player Bullet collision dinamics
        gameLogic.pBulletsCollisionDynamics();

        // Enemy Bullet collision dinamics
        gameLogic.eBulletsCollisionDynamics();

        // Update game state
        gameLogic.updateGameState();

        //////////////////////////////////////////////////////////////////////
        // Display
        //////////////////////////////////////////////////////////////////////

        // Draw Border & Interface
        display.drawGameBorder();
        display.drawPlayerInterface(gameLogic.playerGetInfo());

        // Draw Player Ship
        display.drawCharToPosition(gameLogic.playerGetPosition(), L'W');

        // Draw Player Bullets
        display.drawCharToPositionsInVector(gameLogic.pBulletsGetVec(), L'.');

        // Draw Enemy Bullets
        display.drawCharToPositionsInVector(gameLogic.eBulletsGetVec(), L'°');

        // Draw Enemies
        display.drawCharToPositionsInVector(gameLogic.enemyGetVec(), L'Y');

        // Update Frame
        display.updateFrame();

        // Write game state message
        display.writeGameStateMessage(gameLogic.getGameState());

        if (gameLogic.getGameState() != GAME_IN_PROGRESS)
        {
            char ch = 0;
            while ((ch = _getch()) != '\r')
            {
                continue;
            }
            break;
        }

    }
    
    return 0;
}
