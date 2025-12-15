#include "class_Player.h"


// Default constructor
Player::Player()
{
    name = "Player";
    score = 0;
    lives = 3;
    position.x = 0;
    position.y = 0;
}

// Parametrized constructor
Player::Player(const std::string& str, int s, int l, int pX, int pY)
{
    name = str;
    score = s;
    lives = l;
    position.x = pX;
    position.y = pY;
}

// Copy constructor
Player::Player(const Player& other)
{
    name = other.name;
    score = other.score;
    lives = other.lives;
    position = other.position;
}

// Copy assignment operator
Player& Player::operator=(const Player& other)
{
    if (this != &other)
    {
        name = other.name;
        score = other.score;
        lives = other.lives;
        position.x = other.position.x;
        position.y = other.position.y;
    }
    return *this;
}

// Destructor
Player::~Player() noexcept {};

// Get Player Name
const std::string Player::getName() noexcept
{
    return name;
}

// Set Player Name
void Player::setName(const std::string& name_str)
{
    name = name_str;
}

// Get Player Score
const int Player::getScore() noexcept
{
    return score;
}

// Update Player Score
void Player::updateScore(const int n)
{
    score += n;
}

// Get Player Lives
const int Player::getLives() noexcept
{
    return lives;
}

// Update Player Lives
void Player::updateLives(const int n)
{
    lives += n;
}

// Get Player Position
const Position2D Player::getPosition() noexcept
{
    return position;
}

// Set Player Position
void Player::setPosition(const MovementDirection& movDir)
{
    switch (movDir)
    {
    case MOVE_LEFT:
        position.x--;
        if (position.x < 1) position.x = 1;
        break;

    case MOVE_RIGHT:
        position.x++;
        if (position.x > (SCREEN_WIDTH - 2)) position.x = SCREEN_WIDTH - 2;
        break;
    }
}
