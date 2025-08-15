#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H
#include "Entitymodel.h"
#include "Platform.h"



class Bonus : public Entitymodel {
private:
    EntityType Type;
    std::weak_ptr<Platform> attachedPlatform;
public:
    explicit Bonus(EntityType type) : Type(type) {}
    EntityType getType() const override { return Type;}
    void attachToPlatform(std::shared_ptr<Platform> platform) { attachedPlatform = platform; }
    void updatePosition() {
        if (auto platform = attachedPlatform.lock()) {
            auto platformPos = platform->getcoords();
            float adjustedX;
            float adjustedY;
            if (Type == EntityType::SPRING) {
                adjustedX = platformPos.first + 50;
                adjustedY = platformPos.second + 44;
            } else {
                adjustedX = platformPos.first;
                adjustedY = platformPos.second - 20;
            }
            setcoords(adjustedX, adjustedY); // Position slightly above platform
        }
    }
    Hitbox getHitbox() const override {
        if (Type == EntityType::SPRING) {
            return {x-90, y - 60, 17, 16}; // Adjusted for spring
        } else { // JETPACK
            return {x-40, y -20, 28, 60}; // Adjusted for jetpack
        }
    }
};

#endif // DOODLEJUMP_BONUS_H