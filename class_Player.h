#ifndef PLAYER_H
#define PLAYER_H

#include "class_Position2DVector.h"

class Player
{
private:
    wchar_t name[SCREEN_WIDTH / 2];
    bool nameEntered;
    int score;
    int lives;
    Position2D position;

public:
    // Constructor
    Player();

    // Destructor
    ~Player();

    // Get Player Name
    const wchar_t* getName();

    // Set Player Name
    void setName(const std::string& name_str);

    // Get nameEntered flag
    const bool isNameEntered();

    // Set nameEntered flag
    void setNameEnteredFlag(const bool flag);

    // Get Player Score
    const int getScore();

    // Update Player Score
    void updateScore(const int n);

    // Get Player Lives
    const int getLives();

    // Update Player Lives
    void updateLives(const int n);

    // Get Player Position
    const Position2D getPosition();

    // Set Player Position
    void setPosition(const MovementDirection& movDir);

};

#endif