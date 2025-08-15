
#include "ConcreteFactory.h"
#include "../View/PlatformView.h"
#include "../View/PlayerView.h"
#include "../View/BonusView.h"

std::shared_ptr<Platform> ConcreteFactory::createPlatform(EntityType platformtype) {
    std::shared_ptr<Platform> model = std::make_shared<Platform>();

    std::shared_ptr<PlatformView> view = std::make_shared<PlatformView>();
    view->setTexture(platformtype);

    model->setType(platformtype);
    model->addObserver(view);

    Game::getInstance()->addEntityView(view);
    return model;
}

std::shared_ptr<Player> ConcreteFactory::createPlayer() {
    std::shared_ptr<Player> model = std::make_shared<Player>();

    std::shared_ptr<PlayerView> view = std::make_shared<PlayerView>();
    view->setTexture();
    model->addObserver(view);

    Game::getInstance()->addEntityView(view);
    return model;
}

std::shared_ptr<Bonus> ConcreteFactory::createBonus(EntityType type) {
    std::shared_ptr<Bonus> model = std::make_shared<Bonus>(type);
    std::shared_ptr<BonusView> view = std::make_shared<BonusView>();
    view->setTexture(type);
    model->addObserver(view);
    Game::getInstance()->addEntityView(view);
    return model;
}

std::shared_ptr<BGTile> ConcreteFactory::createBGTile() {
    std::shared_ptr<BGTile> model = std::make_shared<BGTile>();
    std::shared_ptr<BGTileView> view = std::make_shared<BGTileView>();
    model->addObserver(view);
    Game::getInstance()->addEntityView(view);
    return model;
}