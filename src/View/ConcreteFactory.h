#ifndef DOODLEJUMP_CONCRETEFACTORY_H
#define DOODLEJUMP_CONCRETEFACTORY_H

#include "../Model/AbstractFactory.h"
#include <memory>
#include "../Game.h"

class Game;
namespace view {
    class ConcreteFactory : public model::AbstractFactory {
    public:
        std::shared_ptr <model::Platform> createPlatform(EntityType platform) override;

        std::shared_ptr <model::Player> createPlayer() override;

        std::shared_ptr <model::Bonus> createBonus(EntityType type) override;

        std::shared_ptr <model::BGTile> createBGTile() override;
    };
}
#endif // DOODLEJUMP_CONCRETEFACTORY_H