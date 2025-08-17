#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H
#include "../Enums.h"
#include "Entitymodel.h"
#include "../Camera.h"
namespace model {
class Player : public Entitymodel {
private:
    float verticalSpeed = 25.0f;
    HorDirection horDirection;

    bool isOffScreen(const std::shared_ptr<Camera>& camera) const;
    void handleHorizontalMovement();
    void handleVerticalMovement();
    void moveLeft();
    void moveRight();
    void wrapAroundScreen();
    void applyGravity();
    void updateVerticalPosition();

public:
    [[nodiscard]] Hitbox getHitbox() const override { return {x, y + 100, 44, 8}; }

    void setVerticalSpeed(float speed) { verticalSpeed = speed; }

    [[nodiscard]] float getVerticalSpeed() const { return verticalSpeed; }

    [[nodiscard]] EntityType getType() const override { return EntityType::PLAYER; }

    bool move(const std::shared_ptr<Camera>& camera);

    float collidedwithPlayer() override {
        return verticalSpeed; // Return the vertical speed when collided with player
    }
};
}
#endif //DOODLEJUMP_PLAYER_H