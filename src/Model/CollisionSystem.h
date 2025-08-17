#ifndef DOODLEJUMP_COLLISIONSYSTEM_H
#define DOODLEJUMP_COLLISIONSYSTEM_H

#include "Enums.h"
#include "Entities/Player.h"
#include "Entities/Platform.h"
#include "Entities/Bonus.h"
#include <vector>
#include <memory>

namespace model {

/**
 * @brief Stores information about a detected collision.
 */
struct CollisionInfo {
    bool hasCollision; ///< True if a collision occurred
    std::shared_ptr<Entitymodel> collidedEntity; ///< Pointer to the collided entity
    int index; ///< Index of the collided entity in its container
};

/**
 * @brief Handles collision detection between player, platforms, and bonuses.
 */
class CollisionSystem {
public:
    /**
     * @brief Check if two hitboxes intersect.
     * @param a First hitbox.
     * @param b Second hitbox.
     * @return True if hitboxes intersect, false otherwise.
     */
    static bool doHitboxesIntersect(const Hitbox& a, const Hitbox& b);

    /**
     * @brief Detect collision between player and platforms/bonuses.
     * @param player Shared pointer to player.
     * @param platforms Vector of shared pointers to platforms.
     * @param bonuses Vector of shared pointers to bonuses.
     * @return CollisionInfo struct with collision details.
     */
    static CollisionInfo detectCollision(const std::shared_ptr<Player>& player,
                                         const std::vector<std::shared_ptr<Platform>>& platforms,
                                         const std::vector<std::shared_ptr<Bonus>>& bonuses);
};

}

#endif // DOODLEJUMP_COLLISIONSYSTEM_H