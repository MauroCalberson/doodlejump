#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H
#include "../Enums.h"
#include "Entitymodel.h"
#include "../Camera.h"

namespace model {

/**
 * @brief Represents the player entity in the game.
 * Handles movement, collision, and position updates for the player.
 */
class Player : public Entitymodel {
private:
    float verticalSpeed = 25.0f; ///< Current vertical speed of the player
    HorDirection horDirection;   ///< Current horizontal direction

    /**
     * @brief Check if the player is off the visible screen.
     * @param camera Shared pointer to the camera.
     * @return True if off screen, false otherwise.
     */
    bool isOffScreen(const std::shared_ptr<Camera>& camera) const;

    /**
     * @brief Handle horizontal movement based on input.
     */
    void handleHorizontalMovement();

    /**
     * @brief Handle vertical movement (gravity and position).
     */
    void handleVerticalMovement();

    /**
     * @brief Move the player left and wrap around screen if needed.
     */
    void moveLeft();

    /**
     * @brief Move the player right and wrap around screen if needed.
     */
    void moveRight();

    /**
     * @brief Wrap the player around the screen horizontally.
     */
    void wrapAroundScreen();

    /**
     * @brief Apply gravity to the player.
     */
    void applyGravity();

    /**
     * @brief Update the player's vertical position.
     */
    void updateVerticalPosition();

public:
    /**
     * @brief Get the hitbox of the player.
     * @return Hitbox struct.
     */
    [[nodiscard]] Hitbox getHitbox() const override;

    /**
     * @brief Set the vertical speed of the player.
     * @param speed New vertical speed.
     */
    void setVerticalSpeed(float speed);

    /**
     * @brief Get the current vertical speed of the player.
     * @return Vertical speed value.
     */
    [[nodiscard]] float getVerticalSpeed() const;

    /**
     * @brief Get the type of the entity.
     * @return EntityType::PLAYER
     */
    [[nodiscard]] EntityType getType() const override;

    /**
     * @brief Move the player based on input and camera.
     * @param camera Shared pointer to the camera.
     * @return True if player is on screen, false otherwise.
     */
    bool move(const std::shared_ptr<Camera>& camera);

    /**
     * @brief Handle collision with the player.
     * @return Current vertical speed.
     */
    float collidedwithPlayer() override;
};

}

#endif //DOODLEJUMP_PLAYER_H