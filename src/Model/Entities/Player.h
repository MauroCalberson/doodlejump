

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H
#include "../Enums.h"
#include "Entitymodel.h"
class Player : public Entitymodel {
private:
    float verticalSpeed = 25.0f; // Vertical speed of the player
    VertDirection vertdirection;
    HorDirection horDirection;
public:
    //Player() = default;
    Hitbox getHitbox() const override {
        return {x +20, y + 92, 44, 20};
    }
    void setVerticalSpeed(float speed) {
        verticalSpeed = speed;
    }
    float getVerticalSpeed() const {
        return verticalSpeed;
    }
    EntityType getType() const override {
        // Implement the logic to return the type of player
    }
};


#endif //DOODLEJUMP_PLAYER_H
