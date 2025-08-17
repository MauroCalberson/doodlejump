#ifndef DOODLEJUMP_SUBJECT_H
#define DOODLEJUMP_SUBJECT_H

#include "../Observer.h"
#include <vector>
#include <memory>

namespace model {

/**
 * @brief Base class for observable entities.
 * Supports multiple observers and notifies them of changes.
 */
    class Subject {
    private:
        std::vector <std::shared_ptr<Observer>> observers; ///< List of observers

    public:
        Subject() = default;

        virtual ~Subject() = default;

        /**
         * @brief Add an observer to the subject.
         * @param o Shared pointer to observer.
         */
        void addObserver(const std::shared_ptr <Observer> &o);

        /**
         * @brief Notify all observers of a coordinate change.
         * @param x X coordinate.
         * @param y Y coordinate.
         */
        void notifyObservers(const float &x, const float &y);

        /**
         * @brief Notify all observers that the subject is being destroyed.
         */
        void notifyDeletion();

        /**
         * @brief Set the coordinates of the subject.
         * Pure virtual, must be implemented by derived classes.
         */
        virtual void setcoords(float &x, float &y) = 0;

        /**
         * @brief Get the coordinates of the subject.
         * Pure virtual, must be implemented by derived classes.
         */
        virtual std::pair<float, float> getcoords() const = 0;
    };

}

#endif // DOODLEJUMP_SUBJECT_H