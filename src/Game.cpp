#include "Game.h"
#include <stdlib.h>     //for using the function sleep
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
class Game::Impl {
public:
    sf::RenderWindow window;
    std::unique_ptr<World> world;

    Impl() : window(sf::VideoMode(600, 800), "Doodle Jump") {}
};

Game::Game() noexcept : pimpl(std::make_unique<Impl>()) {}

Game::~Game() = default;

void Game::run() {
    const int TICKS_PER_SECOND = 60;
    const std::chrono::milliseconds TICK_DURATION(1000 / TICKS_PER_SECOND);
    pimpl->world = std::make_unique<World>();

    pimpl->world->update();

    while (pimpl->window.isOpen()) {
        auto tick_start = std::chrono::steady_clock::now();

        // ====== Game Logic Tick ======
        //std::cout << "Tick at: " << std::chrono::duration_cast<std::chrono::milliseconds>(tick_start.time_since_epoch()).count() << "ms\n";
        // Update game logic here...
        processEvents();
        update();
        render();
        // =============================

        auto tick_end = std::chrono::steady_clock::now();
        auto tick_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(tick_end - tick_start);

        if (tick_elapsed < TICK_DURATION) {
            std::this_thread::sleep_for(TICK_DURATION - tick_elapsed);
        } else {
            // Optional: log if the tick took too long
            std::cout << "Warning: tick overran by "
                      << (tick_elapsed - TICK_DURATION).count() << " ms\n";
        }

    }
}

void Game::processEvents() {
    sf::Event event;
    horDirection = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? HorDirection::NONE :
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? HorDirection::LEFT :
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? HorDirection::RIGHT :
                   HorDirection::NONE;
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
    // First render background tiles
    for (auto it = bgTileViews.begin(); it != bgTileViews.end();) {
        if (!(*it)->isActive) {
            it = bgTileViews.erase(it);
        } else {
            pimpl->window.draw((*it)->getSprite());
            ++it;
        }
    }
    // Then render bonuses
    for (auto it = bonusViews.begin(); it != bonusViews.end();) {
        if (!(*it)->isActive) {
            it = bonusViews.erase(it);
        } else {
            pimpl->window.draw((*it)->getSprite());
            ++it;
        }
    }
    // Then render platforms
    for (auto it = platformViews.begin(); it != platformViews.end();) {
        if (!(*it)->isActive) {
            it = platformViews.erase(it);
        } else {
            pimpl->window.draw((*it)->getSprite());
            ++it;
        }
    }



    // Finally render the player
    for (auto it = playerViews.begin(); it != playerViews.end();) {
        if (!(*it)->isActive) {
            it = playerViews.erase(it);
        } else {
            pimpl->window.draw((*it)->getSprite());
            ++it;
        }
    }
}
void Game::stop() {
    pimpl->window.close();
    std::cout << "Game stopped." << std::endl;
}