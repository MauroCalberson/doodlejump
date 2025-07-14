// Subject.h
#ifndef DOODLEJUMP_SUBJECT_H
#define DOODLEJUMP_SUBJECT_H

#include "../Observer.h"
#include <vector>
#include <memory>

class Subject {
private:
    std::shared_ptr<Observer> observer;

public:
    Subject() = default;
    virtual ~Subject() = default;
    void addObserver(const std::shared_ptr<Observer>& o) {
        observer = o;
    }
    void notifyObservers(std::pair<float, float>& coords) {
            observer->update(coords.first, coords.second);
    }
    virtual void setcoords(float& x, float& y) = 0;
    virtual std::pair<float,float> getcoords() const = 0;
};

#endif // DOODLEJUMP_SUBJECT_H