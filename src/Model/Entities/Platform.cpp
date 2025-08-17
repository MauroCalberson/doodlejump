#include "Platform.h"

namespace model {

// Default constructor
    Platform::Platform() = default;

// Destructor
    Platform::~Platform() = default;

// Set the type of the platform
    void Platform::setType(EntityType t) {
        type = t;
    }

// Get the type of the platform
    EntityType Platform::getType() const {
        return type;
    }

// Set the coordinates of the platform
    void Platform::setcoords(float &x, float &y) {
        Entitymodel::setcoords(x, y);
    }

// Get the hitbox of the platform
    Hitbox Platform::getHitbox() const {
        // Centered at (x, y) with width 120 and height 16
        return {x - 100, y, 120, 16};
    }

// Set movement bounds for vertical movement
    void Platform::setMovementBounds(float minBound, float maxBound) {
        min = minBound;
        max = maxBound;
    }

// Update horizontal movement for Blue platforms
    void Platform::updateHorizontalMovement() {
        if (movingRight) {
            x += moveSpeed;
            if (x > 540) { // Screen width boundary
                x = 540;
                movingRight = false;
            }
        } else {
            x -= moveSpeed;
            if (x < 60) { // Left boundary with platform width
                x = 60;
                movingRight = true;
            }
        }
    }

// Update vertical movement for Yellow platforms
    void Platform::updateVerticalMovement() {
        if (movingUp) {
            y += moveSpeed;
            if (y > max) {
                y = max;
                movingUp = false;
            }
        } else {
            y -= moveSpeed;
            if (y < min) {
                y = min;
                movingUp = true;
            }
        }
    }

// Update the position of the platform based on its type
    void Platform::updatePosition() {
        if (type == EntityType::Blue) {
            updateHorizontalMovement();
        } else if (type == EntityType::Yellow) {
            updateVerticalMovement();
        }
    }

// Handle collision with the player
    float Platform::collidedwithPlayer() {
        // Collision logic with player can be implemented here
        return 25.0f; // Placeholder return value
    }

}