

#ifndef DOODLEJUMP_ABSTRACTFACTORY_H
#define DOODLEJUMP_ABSTRACTFACTORY_H
#include <memory>
#include "Enums.h"
namespace model {
class Platform;
class Player;
class Bonus;
class BGTile;

class AbstractFactory {
public:
    virtual std::shared_ptr<Platform> createPlatform(EntityType platform) = 0;
    virtual std::shared_ptr<Player> createPlayer() = 0;
    virtual std::shared_ptr<Bonus> createBonus(EntityType type) = 0;
    virtual std::shared_ptr<BGTile> createBGTile() = 0;
    AbstractFactory() = default;
    ~AbstractFactory() = default;
};
}
#endif // DOODLEJUMP_ABSTRACTFACTORY_H
