#include "CollisionSystem.h"

namespace model {

// Check if two hitboxes intersect
    bool CollisionSystem::doHitboxesIntersect(const Hitbox &a, const Hitbox &b) {
        return (a.x < b.x + b.width && a.x + a.width > b.x &&
                a.y < b.y + b.height && a.y + a.height > b.y);
    }

// Detect collision between player and platforms/bonuses
    CollisionInfo CollisionSystem::detectCollision(const std::shared_ptr <Player> &player,
                                                   const std::vector <std::shared_ptr<Platform>> &platforms,
                                                   const std::vector <std::shared_ptr<Bonus>> &bonuses) {
        auto playerHitbox = player->getHitbox();
        float verticalSpeed = player->getVerticalSpeed();

        // Check bonus collisions
        int index = -1;
        for (const auto &bonus: bonuses) {
            index++;
            if (bonus->getType() == EntityType::SPRING && verticalSpeed > 0) {
                continue;
            } else if (doHitboxesIntersect(playerHitbox, bonus->getHitbox())) {
                return {true, bonus, index};
            }
        }

        // Check platform collisions
        if (verticalSpeed <= 0) {
            index = -1;
            for (const auto &platform: platforms) {
                index++;
                if (doHitboxesIntersect(playerHitbox, platform->getHitbox())) {
                    return {true, platform, index};
                }
            }
        }

        return {false, nullptr, -1};
    }

}