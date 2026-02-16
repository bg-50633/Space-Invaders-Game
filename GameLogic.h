#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "class_Position2DVector.h"

class Player
{
private:
    std::string name = "Player";
    int score = 0;
    int lives = 3;
    Position2D position{};

public:
    // Default constructor
    Player();

    // Parametrized constructor
    Player(const std::string& str, int s, int l, int pX, int pY);

    // Copy constructor
    Player(const Player& other);

    // Copy assignment operator
    Player& operator=(const Player& other);

    // Destructor
    ~Player() noexcept;

    // Get Player Name
    const std::string getName() noexcept;

    // Set Player Name
    void setName(const std::string& name_str);

    // Get Player Score
    const int getScore() noexcept;

    // Update Player Score
    void updateScore(const int n);

    // Get Player Lives
    const int getLives() noexcept;

    // Update Player Lives
    void updateLives(const int n);

    // Get Player Position
    const Position2D getPosition() noexcept;

    // Set Player Position
    void setPosition(const MovementDirection& movDir);

};

#endif
