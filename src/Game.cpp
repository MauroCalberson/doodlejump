#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game() noexcept : window(sf::VideoMode(600, 800), "Doodle Jump") {
    if (!font.loadFromFile("textures/Playful Boxes.otf")) {
        throw std::runtime_error("Could not load font");
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10);
}

Game::~Game() = default;

void Game::run() {
    const int TICKS_PER_SECOND = 60;
    const std::chrono::milliseconds TICK_DURATION(1000 / TICKS_PER_SECOND);
    world = std::make_unique<World>();

    while (window.isOpen()) {
        auto tick_start = std::chrono::steady_clock::now();

        processEvents();
        update();
        render();

        auto tick_end = std::chrono::steady_clock::now();
        auto tick_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(tick_end - tick_start);

        if (tick_elapsed < TICK_DURATION) {
            std::this_thread::sleep_for(TICK_DURATION - tick_elapsed);
        } else {
            std::cout << "Warning: tick overran by "
                      << (tick_elapsed - TICK_DURATION).count() << " ms\n";
        }
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            restart();
        }
    }

    if (!isGameOver) {
        bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        if (leftPressed && rightPressed) {
            horDirection = HorDirection::NONE;
        } else if (leftPressed) {
        } else if (rightPressed) {
            horDirection = HorDirection::RIGHT;
        } else {
            horDirection = HorDirection::NONE;
        }
    }

    if (isGameOver) {
        world->update();
        if (world->getScore() > highScore) {
            highScore = world->getScore();
        }
    }
}

void Game::update() {
    world->update();
}

void Game::render() {
    window.clear();
    if (isGameOver) {
        displayGameOver();
    } else {
        displayEntities();
        updateScore(world->getScore());
        window.draw(scoreText);
    }
    window.display();
}

void Game::stop() {
    isGameOver = true;
}

void Game::restart() {
    bgTileViews.clear();
    platformViews.clear();
    bonusViews.clear();
    playerViews.clear();
    isGameOver = false;
    world = std::make_unique<World>();
    horDirection = HorDirection::NONE;
}

void Game::displayGameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over\nHigh Score: " + std::to_string(highScore) + "\nPress SPACE");
    gameOverText.setPosition(100, 300);
    window.draw(gameOverText);
}

void Game::displayEntities() {
    for (auto it = bgTileViews.begin(); it != bgTileViews.end();) {
        if (!(*it)->isActive) {
            it = bgTileViews.erase(it);
        } else {
            window.draw((*it)->getSprite());
            ++it;
        }
    }
    for (auto it = bonusViews.begin(); it != bonusViews.end();) {
        if (!(*it)->isActive) {
            it = bonusViews.erase(it);
        } else {
            window.draw((*it)->getSprite());
            ++it;
        }
    }
    for (auto it = platformViews.begin(); it != platformViews.end();) {
        if (!(*it)->isActive) {
            it = platformViews.erase(it);
        } else {
            window.draw((*it)->getSprite());
            ++it;
        }
    }
    for (auto it = playerViews.begin(); it != playerViews.end();) {
        if (!(*it)->isActive) {
            it = playerViews.erase(it);
        } else {
            window.draw((*it)->getSprite());
            ++it;
        }
    }
}

void Game::updateScore(int score) {
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::addEntityView(std::shared_ptr<EntityView> view) {
    if (auto bgTile = std::dynamic_pointer_cast<BGTileView>(view)) {
        bgTileViews.push_back(bgTile);
    } else if (auto platform = std::dynamic_pointer_cast<PlatformView>(view)) {
        platformViews.push_back(platform);
    } else if (auto player = std::dynamic_pointer_cast<PlayerView>(view)) {
        playerViews.push_back(player);
    } else if (auto bonus = std::dynamic_pointer_cast<BonusView>(view)) {
        bonusViews.push_back(bonus);
    }
}

void Game::removeEntityView(const std::shared_ptr<EntityView>& view) {
    if (auto bgTile = std::dynamic_pointer_cast<BGTileView>(view)) {
        auto it = std::find(bgTileViews.begin(), bgTileViews.end(), bgTile);
        if (it != bgTileViews.end()) bgTileViews.erase(it);
    } else if (auto platform = std::dynamic_pointer_cast<PlatformView>(view)) {
        auto it = std::find(platformViews.begin(), platformViews.end(), platform);
        if (it != platformViews.end()) platformViews.erase(it);
    } else if (auto player = std::dynamic_pointer_cast<PlayerView>(view)) {
        auto it = std::find(playerViews.begin(), playerViews.end(), player);
        if (it != playerViews.end()) playerViews.erase(it);
    } else if (auto bonus = std::dynamic_pointer_cast<BonusView>(view)) {
        auto it = std::find(bonusViews.begin(), bonusViews.end(), bonus);
        if (it != bonusViews.end()) bonusViews.erase(it);
    }
}