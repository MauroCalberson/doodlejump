// Subject.h
#ifndef DOODLEJUMP_SUBJECT_H
#define DOODLEJUMP_SUBJECT_H

#include "../Observer.h"
#include <vector>
#include <memory>

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers; // Allow multiple observers

public:
    Subject() = default;
    virtual ~Subject() = default;

    void addObserver(const std::shared_ptr<Observer>& o) {
        observers.push_back(o); // Add observer to the list
    }

    void notifyObservers(const float& x, const float& y) {
        for (const auto& observer : observers) {
            observer->update(x, y); // Notify all observers
        }
    }
    void notifyDeletion() {
        for (const auto& observer : observers) {
            observer->onDestroy(); // Notify all observers of destruction
        }
    }

    virtual void setcoords(float& x, float& y) = 0;
    virtual std::pair<float, float> getcoords() const = 0;
};

#endif // DOODLEJUMP_SUBJECT_H