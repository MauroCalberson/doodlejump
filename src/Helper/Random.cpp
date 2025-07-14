

#include "Random.h"
// code from chatGPT
int generatenumber(int bound1, int bound2) {
    // Create a random device for seeding
    std::random_device rd;

    // Initialize a random number generator with the random device
    std::mt19937 gen(rd());

    // Define the range for the random number
    std::uniform_int_distribution<> dist(bound1, bound2); // Random number between 1 and 100

    // Generate a random number
    int randomNumber = dist(gen);
    return randomNumber;
}