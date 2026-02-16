#include "RandomGenerator.h"

// Random generator initialization
void RandomGenerator::initRandomGenerator()
{
    // Initialize random number generator
    generator.seed(rand_dev());
}

// 
int RandomGenerator::getRandomNumber(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}