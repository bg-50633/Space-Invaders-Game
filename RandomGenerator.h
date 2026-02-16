#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator
{
private:
    std::random_device rand_dev;
    std::mt19937 generator;

public:
    // Random generator initialization
    void initRandomGenerator();

    // Get a random integer from range [Min, Max]
    int getRandomNumber(int min, int max);

};

#endif