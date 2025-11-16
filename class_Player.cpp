#include "class_Player.h"


// Constructor
Player::Player()
{
    wcscpy_s(name, L"Player");
    nameEntered = FALSE;
    score = 0;
    lives = 3;
    position.x = SCREEN_WIDTH / 2;
    position.y = SCREEN_HEIGHT - 2;
}

// Destructor
Player::~Player() {};

// Get Player Name
const wchar_t* Player::getName()
{
    return name;
}

// Set Player Name
void Player::setName(const std::string& name_str)
{
    std::wstring name_wstr(name_str.begin(), name_str.end());
    std::copy(name_wstr.begin(), name_wstr.end(), name);
    name[name_wstr.length()] = L'\0';
}

// Get nameEntered flag
const bool Player::isNameEntered()
{
    return nameEntered;
}

// Set nameEntered flag
void Player::setNameEnteredFlag(const bool flag)
{
    nameEntered = flag;
}

// Get Player Score
const int Player::getScore()
{
    return score;
}

// Update Player Score
void Player::updateScore(const int n)
{
    score += n;
}

// Get Player Lives
const int Player::getLives()
{
    return lives;
}

// Update Player Lives
void Player::updateLives(const int n)
{
    lives += n;
}

// Get Player Position
const Position2D Player::getPosition()
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
