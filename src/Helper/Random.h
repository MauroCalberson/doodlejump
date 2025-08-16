// Random.h
#ifndef DOODLEJUMP_RANDOM_H
#define DOODLEJUMP_RANDOM_H

#include <random>

class Random {
private:
    std::mt19937 generator;

    // Private constructor
    Random() : generator(std::random_device{}()) {}

    // Delete copy constructor and assignment operator
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

public:
    static Random& getInstance() {
        static Random instance;
        return instance;
    }

    float getFloat(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }

    int getInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
};

#endif // DOODLEJUMP_RANDOM_H