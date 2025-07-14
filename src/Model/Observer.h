// Observer.h
#ifndef DOODLEJUMP_OBSERVER_H
#define DOODLEJUMP_OBSERVER_H

class Observer {
public:
    virtual void update(float x, float y) = 0; // Called when the subject changes
    virtual ~Observer() = default;
};

#endif // DOODLEJUMP_OBSERVER_H