

#ifndef DOODLEJUMP_ENTITYMODEL_H
#define DOODLEJUMP_ENTITYMODEL_H

#include "../../Helper/Random.h"
#include "Subject.h"
#include "../Enums.h"
struct Hitbox {
    float x;
    float y;
    float width;
    float height;
};
class Entitymodel : public Subject {
protected:
    float x;
    float y;

public:
    //Entitymodel() = default;
    void setcoords(float& x, float& y) override {
        this->x = x;
        this->y = y;
    }

    [[nodiscard]] std::pair<float, float> getcoords() const override {
        return {x, y};
    }
    virtual Hitbox getHitbox() const {
        return {x, y, 0, 0}; // Default hitbox, should be overridden in derived classes
    }
    virtual EntityType getType() const = 0; // Pure virtual function to get the type of the entity
};


#endif // DOODLEJUMP_ENTITYMODEL_H
