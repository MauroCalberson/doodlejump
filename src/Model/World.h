#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include "AbstractFactory.h"
#include "Entities/Player.h"
#include "Camera.h"
#include "CollisionSystem.h"
#include "../Helper/Random.h"
#include <memory>

namespace model {

class PlatformManager;
class BonusManager;
class BGTileManager;

/**
 * @brief Main game world class. Handles entity management, game logic, and score.
 */
class World {
public:
    /**
     * @brief Construct the world and initialize entities.
     * @param factory Abstract factory for creating entities.
     */
    explicit World(std::unique_ptr<AbstractFactory> factory);

    /**
     * @brief Destroy the world and clean up resources.
     */
    ~World();

    /**
     * @brief Update the world state (entities, collisions, camera, score).
     */
    void update();

    /**
     * @brief Set up initial entities and game state.
     */
    void setup();

    /**
     * @brief Get the current score.
     * @return Current score.
     */
    [[nodiscard]] int getScore() const { return score; }

    bool stop = false; ///< Indicates if the game should stop (e.g., player fell off screen)

private:
    /**
     * @brief Handle collisions between player and platforms/bonuses.
     */
    void handleCollisions();

    /**
     * @brief Update game difficulty based on camera position.
     */
    void updateDifficulty();

    /**
     * @brief Calculate coordinates for a new platform.
     * @return Pair of x and y coordinates.
     */
    std::pair<float, float> calcPlatformCoords();

    /**
     * @brief Generate a new platform and possibly a bonus.
     * @return Shared pointer to the new platform.
     */
    std::shared_ptr<Platform> generatePlatform();

    /**
     * @brief Create initial background tiles.
     */
    void createBackgroundTiles();

    /**
     * @brief Notify all entity observers of their updated positions.
     */
    void notifyEntityObservers();

    /**
     * @brief Update the score based on camera position.
     */
    void updateScore();

    std::shared_ptr<Camera> camera; ///< Camera for view normalization
    std::shared_ptr<Player> player; ///< Player entity
    std::unique_ptr<AbstractFactory> factory; ///< Factory for creating entities
    std::unique_ptr<PlatformManager> platformManager; ///< Platform manager
    std::unique_ptr<BonusManager> bonusManager; ///< Bonus manager
    std::unique_ptr<BGTileManager> bgTileManager; ///< Background tile manager
    float difficulty = 0.0f; ///< Current game difficulty
    int score = 0; ///< Current score
};

}

#endif // DOODLEJUMP_WORLD_H