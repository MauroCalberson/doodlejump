#ifndef DOODLEJUMP_ENTITYMODEL_H
#define DOODLEJUMP_ENTITYMODEL_H

#include "Subject.h"
#include "../Enums.h"

namespace model {

/**
 * @brief Struct representing a rectangular hitbox.
 */
    struct Hitbox {
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;
    };

/**
 * @brief Abstract base class for all game entities.
 * Inherits from Subject for observer pattern support.
 */
    class Entitymodel : public Subject {
    protected:
        float x = 0; ///< X coordinate of the entity
        float y = 0; ///< Y coordinate of the entity

    public:
        Entitymodel() = default;

        virtual ~Entitymodel() = default;

        /**
         * @brief Set the coordinates of the entity.
         * @param x X position.
         * @param y Y position.
         */
        void setcoords(float &x, float &y) override;

        /**
         * @brief Get the coordinates of the entity.
         * @return Pair of floats (x, y).
         */
        [[nodiscard]] std::pair<float, float> getcoords() const override;

        /**
         * @brief Get the hitbox of the entity.
         * @return Hitbox struct.
         */
        [[nodiscard]] virtual Hitbox getHitbox() const;

        /**
         * @brief Get the type of the entity.
         * @return EntityType enum value.
         */
        [[nodiscard]] virtual EntityType getType() const = 0;

        /**
         * @brief Handle collision with the player.
         * @return Resulting velocity after collision.
         */
        virtual float collidedwithPlayer() = 0;
    };

}

#endif // DOODLEJUMP_ENTITYMODEL_H