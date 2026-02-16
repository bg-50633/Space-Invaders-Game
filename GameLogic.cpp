#include "GameLogic.h"


// Constructor
GameLogic::GameLogic(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    gameState = GAME_IN_PROGRESS;
    enemyMovementDirection = MOVE_LEFT;

    keyPressedLeft_B = FALSE;
    keyPressedRight_B = FALSE;
    keyPressedLeftOld_B = FALSE;
    keyPressedRightOld_B = FALSE;
    keyPressedSpace_B = FALSE;
    keyPressedSpaceOld_B = FALSE;
    timeDelay = std::chrono::milliseconds(100);
}

// Destructor
GameLogic::~GameLogic() {};

//////////////////////////////////////////////////////////////////////
// Player member functions
//////////////////////////////////////////////////////////////////////

// Initialize Player
void GameLogic::playerInit()
{
    player.name = L"Player 1";
    player.score = 0;
    player.lives = 3;
    player.position.x = 25;
    player.position.y = 48;
}

// Get Player Name
const std::wstring GameLogic::playerGetName() const noexcept
{
    return player.name;
}

// Set Player Name
void GameLogic::playerSetName(const std::wstring& name_str)
{
    player.name = name_str;
}

// Get Player Score
const int GameLogic::playerGetScore() const noexcept
{
    return player.score;
}

// Update Player Score
void GameLogic::playerUpdateScore(const int n)
{
    player.score += n;
}

// Get Player Lives
const int GameLogic::playerGetLives() const noexcept
{
    return player.lives;
}

// Update Player Lives
void GameLogic::playerUpdateLives(const int n)
{
    player.lives += n;
}

// Get Player Position
const Position2D GameLogic::playerGetPosition() const noexcept
{
    return player.position;
}

// Set Player Position
void GameLogic::playerSetPosition(const MovementDirection& movDir)
{
    switch (movDir)
    {
    case MOVE_LEFT:
        player.position.x--;
        if (player.position.x < 1) player.position.x = 1;
        break;

    case MOVE_RIGHT:
        player.position.x++;
        if (player.position.x > (screenWidth - 2)) player.position.x = screenWidth - 2;
        break;
    }
}

// Get Player Info
const Player GameLogic::playerGetInfo() noexcept
{
    return player;
}

//////////////////////////////////////////////////////////////////////
// pBullets member functions
//////////////////////////////////////////////////////////////////////

// Player bullet shot
void GameLogic::pBulletShot()
{
    pBulletsVec.addPos(player.position);
}

// Get pBulletsVec
Position2DVector& GameLogic::pBulletsGetVec()
{
    return pBulletsVec;
}

// Move player bullets
void GameLogic::pBulletsMove()
{
    Position2D temp{};
    for (size_t i = 0; i < pBulletsVec.getVectorSize(); i++)
    {
        temp = pBulletsVec.getPos(i);
        if (temp.y <= 4)
        {
            pBulletsVec.removePos(temp);
        }
        else
        {
            pBulletsVec.updatePos(i, MOVE_UP);
        }
    }
}

// Player Bullet collision dinamics
void GameLogic::pBulletsCollisionDynamics()
{
    Position2D temp{};
    for (size_t i = 0; i < pBulletsVec.getVectorSize(); i++)
    {
        temp = pBulletsVec.getPos(i);
        if (enemyVec.isContaining(temp))
        {
            pBulletsVec.removePos(temp);
            enemyVec.removePos(temp);
            playerUpdateScore(10);
        }
    }
}

//////////////////////////////////////////////////////////////////////
// enemyVec member functions
//////////////////////////////////////////////////////////////////////

// Initialize enemyVec
void GameLogic::enemyVecInit()
{
    // Set enemy initial positions
    enemyVec.addPos(15, 7);
    enemyVec.addPos(14, 6);
    enemyVec.addPos(16, 6);
    enemyVec.addPos(15, 5);
    enemyVec.addPos(13, 5);
    enemyVec.addPos(17, 5);
    
    enemyVec.addPos(25, 7);
    enemyVec.addPos(24, 6);
    enemyVec.addPos(26, 6);
    enemyVec.addPos(25, 5);
    enemyVec.addPos(23, 5);
    enemyVec.addPos(27, 5);
    
    enemyVec.addPos(35, 7);
    enemyVec.addPos(34, 6);
    enemyVec.addPos(36, 6);
    enemyVec.addPos(35, 5);
    enemyVec.addPos(33, 5);
    enemyVec.addPos(37, 5);

    enemyVec.addPos(20, 11);
    enemyVec.addPos(19, 10);
    enemyVec.addPos(21, 10);
    enemyVec.addPos(20, 9);
    enemyVec.addPos(18, 9);
    enemyVec.addPos(22, 9);

    enemyVec.addPos(30, 11);
    enemyVec.addPos(29, 10);
    enemyVec.addPos(31, 10);
    enemyVec.addPos(30, 9);
    enemyVec.addPos(28, 9);
    enemyVec.addPos(32, 9);

    enemyVec.addPos(25, 15);
    enemyVec.addPos(24, 14);
    enemyVec.addPos(26, 14);
    enemyVec.addPos(25, 13);
    enemyVec.addPos(23, 13);
    enemyVec.addPos(27, 13);

    // Set enemy initial movement direction
    enemyMovementDirection = MOVE_LEFT;
}

// Get enemyVec
Position2DVector& GameLogic::enemyGetVec()
{
    return enemyVec;
}

// Move enemies
void GameLogic::enemyVecMove()
{
    Position2D temp{};
    Position2D borderEnemy{};

    switch (enemyMovementDirection)
    {
    case MOVE_LEFT:
        // Search for the most LEFT enemy position
        for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
        {
            temp = enemyVec.getPos(i);
            if (i == 0)
            {
                borderEnemy = enemyVec.getPos(i);
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
            for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
            {
                enemyVec.updatePos(i, MOVE_LEFT);
            }
        }
        else
        {
            enemyMovementDirection = MOVE_RIGHT;
            for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
            {
                enemyVec.updatePos(i, MOVE_RIGHT);
                enemyVec.updatePos(i, MOVE_DOWN);
            }
        }
        break;

    case MOVE_RIGHT:
        // Search for the most RIGHT enemy position
        for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
        {
            temp = enemyVec.getPos(i);
            if (i == 0)
            {
                borderEnemy = enemyVec.getPos(i);
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
        if (borderEnemy.x < screenWidth - 2)
        {
            for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
            {
                enemyVec.updatePos(i, MOVE_RIGHT);
            }
        }
        else
        {
            enemyMovementDirection = MOVE_LEFT;
            for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
            {
                enemyVec.updatePos(i, MOVE_LEFT);
                enemyVec.updatePos(i, MOVE_DOWN);
            }
        }
        break;
    }
}

//////////////////////////////////////////////////////////////////////
// eBullets member functions
//////////////////////////////////////////////////////////////////////

// Spawn enemy bullets
void GameLogic::eBulletsSpawn()
{
    Position2D temp{};
    for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
    {
        temp = enemyVec.getPos(i);
        if (randomGenerator.getRandomNumber(1, 100) <= 1)
        {
            eBulletsVec.addPos(temp);
        }
    }
}

// Get eBulletsVec
Position2DVector& GameLogic::eBulletsGetVec()
{
    return eBulletsVec;
}

// Move enemy bullets
void GameLogic::eBulletsMove()
{
    Position2D temp{};
    for (size_t i = 0; i < eBulletsVec.getVectorSize(); i++)
    {
        temp = eBulletsVec.getPos(i);
        if (temp.y >= screenHeight - 2)
        {
            eBulletsVec.removePos(temp);
        }
        else
        {
            eBulletsVec.updatePos(i, MOVE_DOWN);
        }
    }
}

// Enemy Bullet collision dinamics
void GameLogic::eBulletsCollisionDynamics()
{
    if (eBulletsVec.isContaining(playerGetPosition()))
    {
        eBulletsVec.removePos(playerGetPosition());
        playerUpdateLives(-1);
    }
}

//////////////////////////////////////////////////////////////////////
// Other
//////////////////////////////////////////////////////////////////////

// Random generator initialization
void GameLogic::randomGeneratorInit()
{
    randomGenerator.initRandomGenerator();
}

// Get keyboard input
void GameLogic::getKeyboardInput()
{
    auto startTime = std::chrono::system_clock::now();
    while ((std::chrono::system_clock::now() - startTime) < timeDelay)
    {
        keyPressedRight_B = (0x8000 & GetAsyncKeyState(VK_RIGHT)) != 0;
        keyPressedLeft_B  = (0x8000 & GetAsyncKeyState(VK_LEFT)) != 0;
        keyPressedSpace_B = (0x8000 & GetAsyncKeyState(VK_SPACE)) != 0;

        if (keyPressedRight_B && !keyPressedRightOld_B)
        {
            playerSetPosition(MOVE_RIGHT);
        }
        if (keyPressedLeft_B && !keyPressedLeftOld_B)
        {
            playerSetPosition(MOVE_LEFT);
        }

        if (keyPressedSpace_B && !keyPressedSpaceOld_B)
        {
            pBulletShot();
        }

        keyPressedRightOld_B = keyPressedRight_B;
        keyPressedLeftOld_B = keyPressedLeft_B;
        keyPressedSpaceOld_B = keyPressedSpace_B;
    }
}

// Update game state
void GameLogic::updateGameState()
{
    if (enemyVec.isEmpty())
    {
        gameState = PLAYER_WON;
    }

    else if (player.lives <= 0)
    {
        gameState = PLAYER_HAS_ZERO_LIVES;
    }

    else
    {
        // Search if an enemy has reached the player
        for (size_t i = 0; i < enemyVec.getVectorSize(); i++)
        {
            if (enemyVec.getPos(i).y >= 48)
            {
                gameState = ENEMIES_REACHED_PLAYER;
                break;
            }
        }
    }
}

// Get game state
const GameState GameLogic::getGameState() const noexcept
{
    return gameState;
}