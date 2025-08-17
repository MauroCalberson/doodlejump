#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H
#include "Entitymodel.h"
#include "Platform.h"

namespace model {

class Bonus : public Entitymodel {
protected:
    EntityType Type;
    std::weak_ptr<Platform> attachedPlatform;

public:
    //Bonus(EntityType type) : Type(type) {}
    void attachToPlatform(const std::shared_ptr<Platform>& platform) { attachedPlatform = platform; }
    virtual void updateBonusPosition() = 0;
    virtual float collidedwithPlayer() = 0; // Pure virtual function to handle player collision
    [[nodiscard]] Hitbox getHitbox() const override = 0; // Pure virtual function to get the hitbox of the bonus
};
class Spring : public Bonus {
private:
    float bounceHeight = 56.509f; // Default bounce height for spring
public:
    Spring() = default;

    [[nodiscard]] float collidedwithPlayer() override {
        return bounceHeight; // Return the bounce height when collided with player
    }
    [[nodiscard]] EntityType getType() const override {
        return EntityType::SPRING; // Return the type of the bonus
    }
    void updateBonusPosition() override {
        if (auto platform = attachedPlatform.lock()) {
            auto platformPos = platform->getcoords();
            float adjustedX = platformPos.first + 50;
            float adjustedY = platformPos.second + 44;
            setcoords(adjustedX, adjustedY); // Position slightly above platform
        }
    }
    [[nodiscard]] Hitbox getHitbox() const override {
        return {x - 100, y - 60, 17, 16}; // Adjusted for spring
    }
};
class Jetpack : public Bonus {
private:
    float boostSpeed = 100.0f; // Default boost speed for jetpack
public:
    Jetpack() = default;
    [[nodiscard]] float collidedwithPlayer() override {
        return boostSpeed; // Return the boost speed when collided with player
    }
    [[nodiscard]] EntityType getType() const override {
        return EntityType::JETPACK; // Return the type of the bonus
    }
    void updateBonusPosition() override {
        if (auto platform = attachedPlatform.lock()) {
            auto platformPos = platform->getcoords();
            float adjustedX = platformPos.first;
            float adjustedY = platformPos.second - 20;
            setcoords(adjustedX, adjustedY); // Position slightly above platform
        }
    }
    [[nodiscard]] Hitbox getHitbox() const override {
        return {x - 40, y - 20, 28, 60}; // Adjusted for jetpack
    }
};
}
#endif // DOODLEJUMP_BONUS_H