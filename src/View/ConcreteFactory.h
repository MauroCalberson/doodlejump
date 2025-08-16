#ifndef DOODLEJUMP_CONCRETEFACTORY_H
#define DOODLEJUMP_CONCRETEFACTORY_H

#include "../Model/AbstractFactory.h"
#include "../Model/Entities/Platform.h"
#include "../Model/Entities/Player.h"
#include "../Model/Entities/Bonus.h"
#include "../Model/Entities/BGTile.h"
#include <memory>
#include "../Game.h"
class Game;
class ConcreteFactory : public AbstractFactory {
public:
    std::shared_ptr<Platform> createPlatform(EntityType platform) override;
    std::shared_ptr<Player> createPlayer() override;
    std::shared_ptr<Bonus> createBonus(EntityType type) override;
    std::shared_ptr<BGTile> createBGTile() override;
};

#endif // DOODLEJUMP_CONCRETEFACTORY_H