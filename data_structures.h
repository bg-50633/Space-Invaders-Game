#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Is data_structures good name? What does it tell us?

// Should width and height be here?
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 50


enum MovementDirection
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

// Is there a std::cpp class that we can use instead?
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