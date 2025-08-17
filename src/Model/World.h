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
class World {
public:
    explicit World(std::unique_ptr<AbstractFactory> factory);
    ~World();
    void update();
    void setup();
    [[nodiscard]] int getScore() const { return score; }
    bool stop = false;
private:
    void handleCollisions();
    void updateDifficulty();
    std::pair<float, float> calcPlatformCoords();
    std::shared_ptr<Platform> generatePlatform();
    void createBackgroundTiles();
    void notifyEntityObservers();
    void updateScore() {
        auto cameraPos = camera->getPosition();
        score = static_cast<int>(-cameraPos.second);
        if (score < 0) score = 0;
    }
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Player> player;
    std::unique_ptr<AbstractFactory> factory;
    std::unique_ptr<PlatformManager> platformManager;
    std::unique_ptr<BonusManager> bonusManager;
    std::unique_ptr<BGTileManager> bgTileManager;
    float difficulty = 0.0f;
    int score = 0;
};
}

#endif // DOODLEJUMP_WORLD_H
