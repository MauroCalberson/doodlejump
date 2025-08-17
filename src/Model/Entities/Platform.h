// Platform.h
#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H
#include "Entitymodel.h"
#include "../Enums.h"
namespace model {
class Platform : public Entitymodel {

private:
    EntityType type;
    float max = 0;
    float min = 800;
    float moveSpeed = 3;
    bool movingRight = true; // Direction flag for blue platforms
    bool movingUp = true;    // Direction flag for yellow platforms

    void updateHorizontalMovement() {
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

    void updateVerticalMovement() {
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

public:
    Platform() = default;
    ~Platform() override = default;
    void setType(EntityType t) { type = t; }
    [[nodiscard]] EntityType getType() const override { return type; }
    void setcoords(float& x, float& y) override { Entitymodel::setcoords(x, y); }
    [[nodiscard]] Hitbox getHitbox() const override {
        return {x - 100, y, 120, 16}; // Centered at (x, y) with width 120 and height 8
    }
    void setMovementBounds(float minBound, float maxBound) {
        min = minBound;
        max = maxBound;
    }

    void updatePosition() {
        if (type == EntityType::Blue) {
            updateHorizontalMovement();
        } else if (type == EntityType::Yellow) {
            updateVerticalMovement();
        }
    }
};
}
#endif // DOODLEJUMP_PLATFORM_H