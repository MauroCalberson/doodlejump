#include "Entitymodel.h"
#include "../Observer.h"

namespace model {

// Set the coordinates of the entity
void Entitymodel::setcoords(float& x, float& y) {
    this->x = x;
    this->y = y;
}

// Get the coordinates of the entity
std::pair<float, float> Entitymodel::getcoords() const {
    return {x, y};
}

// Get the hitbox of the entity (default implementation)
// Should be overridden in derived classes for specific hitbox sizes
Hitbox Entitymodel::getHitbox() const {
    return {x, y, 0, 0};
}

}