
#include "ConcreteFactory.h"
#include "../View/PlatformView.h"
#include "../View/PlayerView.h"

std::shared_ptr<Platform> ConcreteFactory::createPlatform(PlatformType platformtype) {
    std::shared_ptr<Platform> model = std::make_shared<Platform>();

    std::shared_ptr<PlatformView> view = std::make_shared<PlatformView>();
    view->setTexture(platformtype);
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

std::shared_ptr<Bonus> ConcreteFactory::createBonus() {
    int s;
    s=s+1;
    return nullptr;
}

std::shared_ptr<BGTile> ConcreteFactory::createBGTile() {
    std::shared_ptr<BGTile> bgTile = std::make_shared<BGTile>();
    /*std::shared_ptr<BGTileView> bgTileView = std::make_shared<EntityView>();
    Game::getInstance()->addEntityView(bgTileView);*/ // Add background tile view to the game
    return bgTile;
}