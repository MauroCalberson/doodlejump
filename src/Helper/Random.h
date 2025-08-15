// src/Helper/Random.h
#ifndef DOODLEJUMP_RANDOM_H
#define DOODLEJUMP_RANDOM_H

#include <random>
// Mersenne Twister random number generator
// source: https://stackoverflow.com/questions/1912199/better-random-algorithm
class Random {
private:
    std::mt19937 generator;

public:
    Random() : generator(std::random_device{}()) {}

    // Generate a random float between min and max
    float getFloat(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }

    // Generate a random integer between min and max
    int getInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
};

#endif // DOODLEJUMP_RANDOM_H