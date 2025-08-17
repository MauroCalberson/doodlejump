#include "Random.h"

// Private constructor initializes the generator with a random seed
Random::Random() : generator(std::random_device{}()) {}

// Get the singleton instance of Random
Random &Random::getInstance() {
    static Random instance;
    return instance;
}

// Generate a random float in the range [min, max]
float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

// Generate a random integer in the range [min, max]
int Random::getInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}