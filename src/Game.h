#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <SFML/Graphics.hpp>
#include "View/EntitytView.h"
#include "Model/Enums.h"
#include <memory>
#include <vector>

namespace model {
    class World;
}

/**
 * @brief Main game class. Handles window, game loop, entity views, and input.
 */
class Game {
private:
    sf::RenderWindow window; ///< Main game window
    std::unique_ptr <model::World> world; ///< Game world
    sf::Font font; ///< Font for score and game over text
    sf::Text scoreText; ///< Text for displaying score

    std::vector <std::shared_ptr<view::BGTileView>> bgTileViews; ///< Background tile views
    std::vector <std::shared_ptr<view::PlatformView>> platformViews; ///< Platform views
    std::vector <std::shared_ptr<view::PlayerView>> playerViews; ///< Player views
    std::vector <std::shared_ptr<view::BonusView>> bonusViews; ///< Bonus views

    HorDirection horDirection = HorDirection::NONE; ///< Current horizontal input direction
    bool isGameOver = false; ///< Game over state
    int highScore = 0; ///< Highest score achieved

public:
    /**
     * @brief Construct the game and initialize window and UI.
     */
    Game()

    noexcept;

    /**
     * @brief Destroy the game.
     */
    ~Game();

    /**
     * @brief Get the singleton instance of the game.
     * @return Pointer to the game instance.
     */
    static Game *getInstance();

    /**
     * @brief Update the score display.
     * @param score Current score.
     */
    void updateScore(int score);

    /**
     * @brief Main game loop.
     */
    void run();

    /**
     * @brief Process window and keyboard events.
     */
    void processEvents();

    /**
     * @brief Update game logic.
     */
    void update();

    /**
     * @brief Render all entities and UI.
     */
    void render();

    /**
     * @brief Draw all entity views.
     */
    void displayEntities();

    /**
     * @brief Display the game over screen.
     */
    void displayGameOver();

    /**
     * @brief Get the current horizontal input direction.
     * @return Reference to HorDirection.
     */
    const HorDirection &getInput() const { return horDirection; }

    /**
     * @brief Set the game to game over state.
     */
    void stop();

    /**
     * @brief Restart the game.
     */
    void restart();

    /**
     * @brief Add an entity view to the appropriate container.
     * @param view Shared pointer to the entity view.
     */
    void addEntityView(const std::shared_ptr <view::EntityView> &view);

    /**
     * @brief Remove an entity view from the appropriate container.
     * @param view Shared pointer to the entity view.
     */
    void removeEntityView(const std::shared_ptr <view::EntityView> &view);
};

#endif // DOODLEJUMP_GAME_H