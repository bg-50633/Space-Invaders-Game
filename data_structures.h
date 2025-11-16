#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 50

enum MovementDirection
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
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

#endif