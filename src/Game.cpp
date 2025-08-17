#include "Game.h"
#include "View/ConcreteFactory.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "View/PlatformView.h"
#include "View/PlayerView.h"
#include "View/BonusView.h"
#include "View/BGTileView.h"
#include "Model/World.h"
#include "Helper/StopWatch.h"

// Construct the game and initialize window and UI
Game::Game() noexcept : window(sf::VideoMode(600, 800), "Doodle Jump") {
    if (!font.loadFromFile("textures/Playful Boxes.otf")) {
        std::cerr <<  " Error: Could not load font" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10);
}

// Destroy the game
Game::~Game() = default;

// Get the singleton instance of the game
Game* Game::getInstance() {
    static Game instance;
    return &instance;
}

// Main game loop
void Game::run() {
    const int TICKS_PER_SECOND = 60;
    const double TICK_DURATION = 1.0 / TICKS_PER_SECOND; // seconds

    auto f = std::make_unique<view::ConcreteFactory>();
    world = std::make_unique<model::World>(std::move(f));

    StopWatch& stopwatch = StopWatch::getInstance();

    while (window.isOpen()) {
        if (world->stop) {
            stop();
        }

        stopwatch.start();

        processEvents();
        update();
        render();

        stopwatch.stop();
        double elapsed = stopwatch.getElapsedTime();

        if (elapsed < TICK_DURATION) {
            std::this_thread::sleep_for(
                std::chrono::duration<double>(TICK_DURATION - elapsed)
            );
        } else {
            std::cout << "Warning: tick overran by "
                      << (elapsed - TICK_DURATION) * 1000 << " ms\n";
        }

        stopwatch.reset();
    }
}

// Process window and keyboard events
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
            horDirection = HorDirection::LEFT;
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

// Update game logic
void Game::update() {
    world->update();
}

// Render all entities and UI
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

// Set the game to game over state
void Game::stop() {
    isGameOver = true;
}

// Restart the game
void Game::restart() {
    bgTileViews.clear();
    platformViews.clear();
    bonusViews.clear();
    playerViews.clear();
    isGameOver = false;
    auto f = std::make_unique<view::ConcreteFactory>();
    world = std::make_unique<model::World>(std::move(f));
    horDirection = HorDirection::NONE;
}

// Display the game over screen
void Game::displayGameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over\nHigh Score: " + std::to_string(highScore) + "\nPress SPACE");
    gameOverText.setPosition(100, 300);
    window.draw(gameOverText);
}

// Draw all entity views
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

// Update the score display
void Game::updateScore(int score) {
    scoreText.setString("Score: " + std::to_string(score));
}

// Add an entity view to the appropriate container
void Game::addEntityView(const std::shared_ptr<view::EntityView>& view) {
    switch (view->getType()) {
    case EntityViewType::BGTile:
        bgTileViews.push_back(std::static_pointer_cast<view::BGTileView>(view));
        break;
    case EntityViewType::Platform:
        platformViews.push_back(std::static_pointer_cast<view::PlatformView>(view));
        break;
    case EntityViewType::Player:
        playerViews.push_back(std::static_pointer_cast<view::PlayerView>(view));
        break;
    case EntityViewType::Bonus:
        bonusViews.push_back(std::static_pointer_cast<view::BonusView>(view));
        break;
    }
}

// Remove an entity view from the appropriate container
void Game::removeEntityView(const std::shared_ptr<view::EntityView>& view) {
    if (auto bgTile = std::dynamic_pointer_cast<view::BGTileView>(view)) {
        auto it = std::find(bgTileViews.begin(), bgTileViews.end(), bgTile);
        if (it != bgTileViews.end()) bgTileViews.erase(it);
    } else if (auto platform = std::dynamic_pointer_cast<view::PlatformView>(view)) {
        auto it = std::find(platformViews.begin(), platformViews.end(), platform);
        if (it != platformViews.end()) platformViews.erase(it);
    } else if (auto player = std::dynamic_pointer_cast<view::PlayerView>(view)) {
        auto it = std::find(playerViews.begin(), playerViews.end(), player);
        if (it != playerViews.end()) playerViews.erase(it);
    } else if (auto bonus = std::dynamic_pointer_cast<view::BonusView>(view)) {
        auto it = std::find(bonusViews.begin(), bonusViews.end(), bonus);
        if (it != bonusViews.end()) bonusViews.erase(it);
    }
}