// StopWatch.h
#ifndef DOODLEJUMP_STOPWATCH_H
#define DOODLEJUMP_STOPWATCH_H

#include <chrono>

class StopWatch {
private:
    std::chrono::steady_clock::time_point startTime;
    bool isRunning;

    // Private constructor
    StopWatch() : isRunning(false) {}
    
    // Delete copy constructor and assignment operator
    StopWatch(const StopWatch&) = delete;
    StopWatch& operator=(const StopWatch&) = delete;

public:
    static StopWatch& getInstance() {
        static StopWatch instance;
        return instance;
    }

    void start() {
        if (!isRunning) {
            startTime = std::chrono::steady_clock::now();
            isRunning = true;
        }
    }

    void stop() {
        isRunning = false;
    }

    double getElapsedTime() {
        if (!isRunning) return 0.0;
        
        auto currentTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
        return duration.count() / 1000.0; // Convert to seconds
    }

    void reset() {
        startTime = std::chrono::steady_clock::now();
    }
};

#endif // DOODLEJUMP_STOPWATCH_H