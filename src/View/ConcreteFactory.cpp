
#include "ConcreteFactory.h"
#include "../View/PlatformView.h"
#include "../View/PlayerView.h"
#include "../View/BonusView.h"
#include "../View/BGTileView.h"
#include "../Model/Entities/Platform.h"
#include "../Model/Entities/Player.h"
#include "../Model/Entities/Bonus.h"
#include "../Model/Entities/BGTile.h"

std::shared_ptr<model::Platform> view::ConcreteFactory::createPlatform(EntityType platformtype) {
    std::shared_ptr<model::Platform> model = std::make_shared<model::Platform>();

    std::shared_ptr<PlatformView> view = std::make_shared<PlatformView>();
    view->setTexture(platformtype);

    model->setType(platformtype);
    model->addObserver(view);

    Game::getInstance()->addEntityView(view);
    return model;
}

std::shared_ptr<model::Player> view::ConcreteFactory::createPlayer() {
    std::shared_ptr<model::Player> model = std::make_shared<model::Player>();

    std::shared_ptr<PlayerView> view = std::make_shared<PlayerView>();
    view->setTexture();
    model->addObserver(view);

    Game::getInstance()->addEntityView(view);
    return model;
}

std::shared_ptr<model::Bonus> view::ConcreteFactory::createBonus(EntityType type) {
    std::shared_ptr<model::Bonus> model;
    if (type == EntityType::SPRING) {
        model = std::make_shared<model::Spring>();
    } else if (type == EntityType::JETPACK) {
        model = std::make_shared<model::Jetpack>();
    } else {
        throw std::invalid_argument("Unknown bonus type");
    }
    auto view = std::make_shared<BonusView>();
    view->setTexture(type);
    model->addObserver(view);
    Game::getInstance()->addEntityView(view);
    return model;
}

std::shared_ptr<model::BGTile> view::ConcreteFactory::createBGTile() {
    std::shared_ptr<model::BGTile> model = std::make_shared<model::BGTile>();
    std::shared_ptr<BGTileView> view = std::make_shared<BGTileView>();
    model->addObserver(view);
    Game::getInstance()->addEntityView(view);
    return model;
}