

#ifndef DOODLEJUMP_ENTITYMODEL_H
#define DOODLEJUMP_ENTITYMODEL_H

#include "Subject.h"
#include "../Enums.h"
namespace model {
class Player;
class Platform;
class Bonus;
class BGTile;
struct Hitbox {
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
};
class Entitymodel : public Subject {
protected:
    float x = 0;
    float y = 0;

public:
    Entitymodel() = default;
    virtual ~Entitymodel() = default;
    void setcoords(float& x, float& y) override {
        this->x = x;
        this->y = y;
    }

    [[nodiscard]] std::pair<float, float> getcoords() const override { return {x, y}; }
    [[nodiscard]] virtual Hitbox getHitbox() const {
        return {x, y, 0, 0}; // Default hitbox, should be overridden in derived classes
    }
    [[nodiscard]] virtual EntityType getType() const = 0; // Pure virtual function to get the type of the entity
    virtual float collidedwithPlayer() = 0;
};
}

#endif // DOODLEJUMP_ENTITYMODEL_H
