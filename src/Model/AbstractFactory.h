

#ifndef DOODLEJUMP_ABSTRACTFACTORY_H
#define DOODLEJUMP_ABSTRACTFACTORY_H
#include <memory>
#include "Entities/Platform.h"
#include "Entities/Bonus.h"
#include "Entities/Player.h"
#include "Entities/BGTile.h"

class PlayerController;
class PlatformController;
class BonusController;
class BGTileController;
class AbstractFactory {
public:
    virtual std::shared_ptr<Platform> createPlatform(EntityType platform) = 0;
    virtual std::shared_ptr<Player> createPlayer() = 0;
    virtual std::shared_ptr<Bonus> createBonus(EntityType type) = 0;
    virtual std::shared_ptr<BGTile> createBGTile() = 0;
    AbstractFactory() = default;
    ~AbstractFactory() = default;
};

#endif // DOODLEJUMP_ABSTRACTFACTORY_H
