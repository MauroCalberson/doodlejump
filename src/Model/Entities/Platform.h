#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "Entitymodel.h"
#include "../Enums.h"

namespace model {

/**
 * @brief Represents a platform entity in the game.
 * Supports static, horizontally moving (Blue), and vertically moving (Yellow) platforms.
 */
    class Platform : public Entitymodel {
    private:
        EntityType type; ///< Type of the platform
        float max = 0; ///< Maximum movement bound (for vertical movement)
        float min = 800; ///< Minimum movement bound (for vertical movement)
        float moveSpeed = 3; ///< Speed of movement
        bool movingRight = true; ///< Direction flag for horizontal movement
        bool movingUp = true; ///< Direction flag for vertical movement

        /**
         * @brief Update horizontal movement for Blue platforms.
         */
        void updateHorizontalMovement();

        /**
         * @brief Update vertical movement for Yellow platforms.
         */
        void updateVerticalMovement();

    public:
        Platform();

        ~Platform() override;

        /**
         * @brief Set the type of the platform.
         * @param t EntityType value.
         */
        void setType(EntityType t);

        /**
         * @brief Get the type of the platform.
         * @return EntityType value.
         */
        [[nodiscard]] EntityType getType() const override;

        /**
         * @brief Set the coordinates of the platform.
         * @param x X position.
         * @param y Y position.
         */
        void setcoords(float &x, float &y) override;

        /**
         * @brief Get the hitbox of the platform.
         * @return Hitbox struct.
         */
        [[nodiscard]] Hitbox getHitbox() const override;

        /**
         * @brief Set movement bounds for vertical movement.
         * @param minBound Minimum Y value.
         * @param maxBound Maximum Y value.
         */
        void setMovementBounds(float minBound, float maxBound);

        /**
         * @brief Update the position of the platform based on its type.
         */
        void updatePosition();

        /**
         * @brief Handle collision with the player.
         * @return Bounce height (default: 25.0f).
         */
        float collidedwithPlayer() override;
    };

}

#endif // DOODLEJUMP_PLATFORM_H