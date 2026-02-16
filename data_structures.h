#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>

enum MovementDirection
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

enum GameState
{
    GAME_IN_PROGRESS,
    PLAYER_WON,
    PLAYER_HAS_ZERO_LIVES,
    ENEMIES_REACHED_PLAYER
};

struct Position2D
{
    int x;
    int y;

    // Constructor
    Position2D(int x = 0, int y = 0) : x(x), y(y) {}

    // Overload + operator
    Position2D operator+(const Position2D& other) const {
        return Position2D(x + other.x, y + other.y);
    }

    // Overload += operator
    Position2D& operator+=(const Position2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Overload == operator
    bool operator==(const Position2D& other) const {
        return (x == other.x) && (y == other.y);
    }
};

struct Player
{
    std::wstring name;
    int score;
    int lives;
    Position2D position;

    // Default constructor
    Player()
    {
        name = L"Player";
        score = 0;
        lives = 0;
        position.x = 0;
        position.y = 0;
    }
};

#endif