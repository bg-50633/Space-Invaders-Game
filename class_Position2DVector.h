#ifndef POSITION_2D_VECTOR_H
#define POSITION_2D_VECTOR_H

#include <iostream>
#include <vector>
#include <Windows.h>

#include "data_structures.h"

using Position2DVector = std::vector<Position2D>

addPostion(int x, int y, Position2DVector& ref); 
posVec.insert({1,2});
posVec.insert(Position2D(1,2));

// What is the point of Position 2D vecotr class?
class Position2DVector {
private:
    std::vector<Position2D> positions;

public:
    // Add position coordinates to vector
    void addPos(int x, int y);

    // Add position to vector
    void addPos(const Position2D& pos);

    // Remove position from vector
    void removePos(const Position2D& pos);

    // Get the number of positions
    size_t getVectorSize();

    // Check if vector is empty
    bool isEmpty();

    // Check if vector is containing a position
    bool isContaining(const Position2D& pos);

    // Update position coordinates
    void updatePos(const size_t& index, const MovementDirection& movDir);

    // Get position by index
    Position2D getPos(size_t index);
};

#endif