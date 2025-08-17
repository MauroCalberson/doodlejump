// Random.h
#ifndef DOODLEJUMP_RANDOM_H
#define DOODLEJUMP_RANDOM_H

#include <random>

/**
 * @brief Singleton class for generating random numbers.
 */
class Random {
private:
    std::mt19937 generator; ///< Mersenne Twister random number generator

    /**
     * @brief Private constructor initializes the generator with a random seed.
     */
    Random();

    // Delete copy constructor and assignment operator to enforce singleton
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

public:
    /**
     * @brief Get the singleton instance of Random.
     * @return Reference to the Random instance.
     */
    static Random& getInstance();

    /**
     * @brief Generate a random float in the range [min, max].
     * @param min Minimum value.
     * @param max Maximum value.
     * @return Random float between min and max.
     */
    float getFloat(float min, float max);

    /**
     * @brief Generate a random integer in the range [min, max].
     * @param min Minimum value.
     * @param max Maximum value.
     * @return Random integer between min and max.
     */
    int getInt(int min, int max);
};

#endif // DOODLEJUMP_RANDOM_H