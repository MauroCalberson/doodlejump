#include "Game.h"

class Game::Impl {
public:
    sf::RenderWindow window;
    std::unique_ptr<World> world;

    Impl() : window(sf::VideoMode(600, 800), "Doodle Jump") {}
};

Game::Game() noexcept : pimpl(std::make_unique<Impl>()) {}

Game::~Game() = default;

void Game::run() {
    pimpl->world = std::make_unique<World>();

    pimpl->world->update();

    while (pimpl->window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (pimpl->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            pimpl->window.close();
    }
}

void Game::update() {
    pimpl->world->update();
}

void Game::render() {
    pimpl->window.clear();
    displayEntities();
    pimpl->window.display();
}

void Game::displayEntities() {
    // Render all entities in the game
    for (const auto& entity : EntityViews) {
        pimpl->window.draw(entity->getSprite());
    }

}