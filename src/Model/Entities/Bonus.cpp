#include "Bonus.h"

namespace model {

// Attach this bonus to a platform
void Bonus::attachToPlatform(const std::shared_ptr<Platform>& platform) {
    attachedPlatform = platform;
}

// Return the bounce height when collided with player
float Spring::collidedwithPlayer() {
    return bounceHeight;
}

// Return the type of the bonus (Spring)
EntityType Spring::getType() const {
    return EntityType::SPRING;
}

// Update the position of the spring based on the platform's position
void Spring::updateBonusPosition() {
    if (auto platform = attachedPlatform.lock()) {
        auto platformPos = platform->getcoords();
        float adjustedX = platformPos.first + 50;
        float adjustedY = platformPos.second + 44;
        setcoords(adjustedX, adjustedY); // Position slightly above platform
    }
}

// Get the hitbox of the spring
Hitbox Spring::getHitbox() const {
    return {x - 100, y - 60, 17, 16};
}

// Return the boost speed when collided with player
float Jetpack::collidedwithPlayer() {
    return boostSpeed;
}

// Return the type of the bonus (Jetpack)
EntityType Jetpack::getType() const {
    return EntityType::JETPACK;
}

// Update the position of the jetpack based on the platform's position
void Jetpack::updateBonusPosition() {
    if (auto platform = attachedPlatform.lock()) {
        auto platformPos = platform->getcoords();
        float adjustedX = platformPos.first;
        float adjustedY = platformPos.second - 20;
        setcoords(adjustedX, adjustedY); // Position slightly above platform
    }
}

// Get the hitbox of the jetpack
Hitbox Jetpack::getHitbox() const {
    return {x - 40, y - 20, 28, 60};
}

}