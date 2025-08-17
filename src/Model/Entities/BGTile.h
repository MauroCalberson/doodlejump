// src/Model/Entities/BGTile.h
#ifndef DOODLEJUMP_BGTILE_H
#define DOODLEJUMP_BGTILE_H

#include "Entitymodel.h"

namespace model {

/**
 * @brief Represents a background tile entity in the game.
 * Inherits from Entitymodel. BGTile does not interact with the player.
 */
    class BGTile : public Entitymodel {
    public:
        /**
         * @brief Default constructor for BGTile.
         */
        BGTile() = default;

        /**
         * @brief Get the type of this entity.
         * @return EntityType::BGTILE
         */
        [[nodiscard]] EntityType getType() const override { return EntityType::BGTILE; }

        /**
         * @brief Handle collision with the player.
         * BGTile has no effect on the player, so always returns 0.0f.
         * @return 0.0f
         */
        float collidedwithPlayer() override { return 0.0f; }
    };

}

#endif // DOODLEJUMP_BGTILE_H