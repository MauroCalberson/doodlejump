#include "StopWatch.h"

// Private constructor initializes the stopwatch as not running
StopWatch::StopWatch() : isRunning(false) {}

// Get the singleton instance of StopWatch
StopWatch &StopWatch::getInstance() {
    static StopWatch instance;
    return instance;
}

// Start the stopwatch if it's not already running
void StopWatch::start() {
    if (!isRunning) {
        startTime = std::chrono::steady_clock::now();
        isRunning = true;
    }
}

// Stop the stopwatch
void StopWatch::stop() {
    isRunning = false;
}

// Get the elapsed time in seconds since the stopwatch was started
double StopWatch::getElapsedTime() {
    if (!isRunning) return 0.0;
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
    return duration.count() / 1000.0;
}

// Reset the stopwatch to the current time
void StopWatch::reset() {
    startTime = std::chrono::steady_clock::now();
}