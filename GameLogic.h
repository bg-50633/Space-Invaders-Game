#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <chrono>

#include "Position2DVector.h"
#include "RandomGenerator.h"

class GameLogic
{
private:
    int screenWidth;
    int screenHeight;
    GameState gameState;

    Player player;

    Position2DVector enemyVec;
    Position2DVector pBulletsVec;
    Position2DVector eBulletsVec;
    MovementDirection enemyMovementDirection;

    RandomGenerator randomGenerator;

    bool keyPressedLeft_B;
    bool keyPressedRight_B;
    bool keyPressedLeftOld_B;
    bool keyPressedRightOld_B;
    bool keyPressedSpace_B;
    bool keyPressedSpaceOld_B;
    std::chrono::milliseconds timeDelay;

public:
    // Constructor
    GameLogic(int width, int height);

    // Destructor
    ~GameLogic();

    //////////////////////////////////////////////////////////////////////
    // Player member functions
    //////////////////////////////////////////////////////////////////////
    
    // Initialize Player
    void playerInit();

    // Get Player Name
    const std::wstring playerGetName() const noexcept;

    // Set Player Name
    void playerSetName(const std::wstring& name_str);

    // Get Player Score
    const int playerGetScore() const noexcept;

    // Update Player Score
    void playerUpdateScore(const int n);

    // Get Player Lives
    const int playerGetLives() const noexcept;

    // Update Player Lives
    void playerUpdateLives(const int n);

    // Get Player Position
    const Position2D playerGetPosition() const noexcept;

    // Set Player Position
    void playerSetPosition(const MovementDirection& movDir);

    // Get Player info
    const Player playerGetInfo() noexcept;
        
    //////////////////////////////////////////////////////////////////////
    // pBullets member functions
    //////////////////////////////////////////////////////////////////////

    // Player bullet shot
    void pBulletShot();

    // Get pBulletsVec
    Position2DVector& pBulletsGetVec();

    // Move player bullets
    void pBulletsMove();

    // Player Bullet collision dinamics
    void pBulletsCollisionDynamics();

    //////////////////////////////////////////////////////////////////////
    // enemyVec member functions
    //////////////////////////////////////////////////////////////////////
    
    // Initialize enemyVec positions
    void enemyVecInit();

    // Get enemyVec
    Position2DVector& enemyGetVec();

    // Move enemies
    void enemyVecMove();
    
    //////////////////////////////////////////////////////////////////////
    // eBullets member functions
    //////////////////////////////////////////////////////////////////////
    
    // Spawn enemy bullets
    void eBulletsSpawn();

    // Get eBulletsVec
    Position2DVector& eBulletsGetVec();

    // Move enemy bullets
    void eBulletsMove();

    // Enemy Bullet collision dinamics
    void eBulletsCollisionDynamics();

    //////////////////////////////////////////////////////////////////////
    // Other
    //////////////////////////////////////////////////////////////////////
    
    // Random generator initialization
    void randomGeneratorInit();

    // Get keyboard input
    void getKeyboardInput();

    // Update game state
    void updateGameState();

    // Get game state
    const GameState getGameState() const noexcept;

};

#endif