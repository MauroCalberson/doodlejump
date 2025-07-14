#ifndef DOODLEJUMP_CONCRETEFACTORY_H
#define DOODLEJUMP_CONCRETEFACTORY_H

#include "../Model/AbstractFactory.h"
#include "../Game.h"

class ConcreteFactory : public AbstractFactory {
public:
    std::shared_ptr<Platform> createPlatform(PlatformType platform) override;
    std::shared_ptr<Player> createPlayer() override;
    std::shared_ptr<Bonus> createBonus() override;
    std::shared_ptr<BGTile> createBGTile() override;
};

#endif // DOODLEJUMP_CONCRETEFACTORY_H