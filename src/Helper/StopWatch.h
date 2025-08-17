#ifndef DOODLEJUMP_STOPWATCH_H
#define DOODLEJUMP_STOPWATCH_H

#include <chrono>

/**
 * @brief Singleton class for measuring elapsed time.
 */
class StopWatch {
private:
    std::chrono::steady_clock::time_point startTime; ///< Start time of the stopwatch
    bool isRunning; ///< Indicates if the stopwatch is running

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    StopWatch();

    // Delete copy constructor and assignment operator
    StopWatch(const StopWatch &) = delete;

    StopWatch &operator=(const StopWatch &) = delete;

public:
    /**
     * @brief Get the singleton instance of StopWatch.
     * @return Reference to the StopWatch instance.
     */
    static StopWatch &getInstance();

    /**
     * @brief Start the stopwatch.
     */
    void start();

    /**
     * @brief Stop the stopwatch.
     */
    void stop();

    /**
     * @brief Get the elapsed time in seconds.
     * @return Elapsed time as double (seconds).
     */
    double getElapsedTime();

    /**
     * @brief Reset the stopwatch to the current time.
     */
    void reset();
};

#endif // DOODLEJUMP_STOPWATCH_H