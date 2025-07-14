

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H
#include "../View/ConcreteFactory.h"
#include "Entities/Entitymodel.h"
#include "Entities/Platform.h"
#include "Entities/Player.h"
#include "Camera.h"
#include <memory>
#include <vector>
class PlayerController;
class PlatformController;
class BonusController;
class TileController;
class TextController;
class WorldGenerator;
class CameraController;
class World {


public:
    World();
    void update();
    void setup();
    bool detectCollision();
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Platform>> platforms;
};

#endif // DOODLEJUMP_WORLD_H
