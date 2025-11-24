#ifndef PLAYER_H
#define PLAYER_H

#include "class_Position2DVector.h"

class Player
{
private:
    // What type is more suited for name?
    wchar_t name[SCREEN_WIDTH / 2];
    // Why is nameEntered needed? Do functions releated to this need to exist?
    bool nameEntered;
    int score;
    int lives;
    Position2D position;

public:
    // Constructor
    // throw exception if name not valid
    Player(std::string name);

    // If we need destructor, what else do we need?
    // Destructor
    ~Player();

    // Get Player Name
    const wchar_t* getName();

    // Set Player Name
    // How many times do we need to set player name, is there a better place to do it?
    void setName(const std::string& name_str);

    // Get nameEntered flag
    const bool isNameEntered();

    // Set nameEntered flag
    void setNameEnteredFlag(const bool flag);

    // Get Player Score
    int getScore() ;

    // Update Player Score
    void updateScore(const int n);

    // Get Player Lives
    int getLives() const;

    // Update Player Lives
    void updateLives(const int n);

    // Get Player Position
    const Position2D getPosition();

    // Set Player Position
    void setPosition(const MovementDirection& movDir);

};

#endif