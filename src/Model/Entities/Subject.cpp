#include "Subject.h"

namespace model {

// Add an observer to the subject
void Subject::addObserver(const std::shared_ptr<Observer>& o) {
    observers.push_back(o);
}

// Notify all observers of a coordinate change
void Subject::notifyObservers(const float& x, const float& y) {
    for (const auto& observer : observers) {
        observer->update(x, y);
    }
}

// Notify all observers that the subject is being destroyed
void Subject::notifyDeletion() {
    for (const auto& observer : observers) {
        observer->onDestroy();
    }
}

}