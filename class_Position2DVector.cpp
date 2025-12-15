#include "class_Position2DVector.h"

// Add position coordinates to vector
void Position2DVector::addPos(int x, int y)
{
    Position2D pos = { x, y };
    auto it = std::find(positions.begin(), positions.end(), pos);
    if (it == positions.end())
    {
        positions.push_back(pos);
    }
}

// Add position to vector
void Position2DVector::addPos(const Position2D& pos)
{
    auto it = std::find(positions.begin(), positions.end(), pos);
    if (it == positions.end())
    {
        positions.push_back(pos);
    }
}

// Remove position from vector
void Position2DVector::removePos(const Position2D& pos)
{
    auto it = std::find(positions.begin(), positions.end(), pos);
    if (it != positions.end()) 
    {
        positions.erase(it);
    }
}

// Get the number of positions
size_t Position2DVector::getVectorSize()
{
    return positions.size();
}

// Check if vector is empty
bool Position2DVector::isEmpty()
{
    return positions.empty();
}

// Check if vector is containing a position
bool Position2DVector::isContaining(const Position2D& pos) 
{
    auto it = std::find(positions.begin(), positions.end(), pos);
    if (it != positions.end())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// Update position coordinates
void Position2DVector::updatePos(const size_t& index, const MovementDirection& movDir)
{
    Position2D temp{};
    switch (movDir)
    {
    case MOVE_UP:
        temp = { 0, -1 };
        positions[index] += temp;
        break;

    case MOVE_DOWN:
        temp = { 0, 1 };
        positions[index] += temp;
        break;

    case MOVE_LEFT:
        temp = { -1, 0 };
        positions[index] += temp;
        break;

    case MOVE_RIGHT:
        temp = { 1, 0 };
        positions[index] += temp;
        break;
    }
}

// Get position by index
Position2D Position2DVector::getPos(size_t index)
{
    if (index >= 0 && index < positions.size())
    {
        return positions[index];
    }
    throw std::out_of_range("Invalid index");
}

// Get positions vector
const std::vector<Position2D> Position2DVector::getPosVec()
{
    return positions;
}