

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H
#include "../View/ConcreteFactory.h"
#include "Entities/Entitymodel.h"
#include "Entities/Platform.h"
#include "Entities/Player.h"
#include "Camera.h"
#include <memory>
#include <vector>
#include "../Helper/Random.h"

struct CollisionInfo {
    bool hasCollision;
    std::shared_ptr<Entitymodel> collidedEntity;
    int index;
};
class World {

//using the middle of the object as the coordinate
public:
    World(const std::string& configFilePath = "src/config.txt");
    void update();
    void setup();
    [[nodiscard]] std::pair<float,float> calcPlatformCoords();
    std::shared_ptr<Platform> generatePlatform();
    void updateEntities();
    CollisionInfo detectCollision();
    void movePlayer();
    void handleCollisions(float& newY);
    void updateDifficulty();
    void createBackgroundTiles();
private:
    Random random;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Bonus>> bonuses;
    std::vector<std::shared_ptr<Platform>> platforms;
    std::vector<std::shared_ptr<BGTile>> backgroundTiles;
    std::unique_ptr<AbstractFactory> factory;
    float highestTileY = 0.0f; // Current highest tile Y position
    float maxplatformheight = 800; // current height of highest platform
    float difficulty = 0;
    float prevCameraY = 0.0f; // Previous camera Y position for platform updates
};

#endif // DOODLEJUMP_WORLD_H
