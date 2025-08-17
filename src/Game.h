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
class Game {
private:
    sf::RenderWindow window;
    std::unique_ptr<model::World> world;
    sf::Font font;
    sf::Text scoreText;

    std::vector<std::shared_ptr<view::BGTileView>> bgTileViews;
    std::vector<std::shared_ptr<view::PlatformView>> platformViews;
    std::vector<std::shared_ptr<view::PlayerView>> playerViews;
    std::vector<std::shared_ptr<view::BonusView>> bonusViews;

    HorDirection horDirection = HorDirection::NONE;
    bool isGameOver = false;
    int highScore = 0;

public:
    Game() noexcept;
    ~Game();

    static Game* getInstance() {
        static Game instance;
        return &instance;
    }

    void updateScore(int score);
    void run();
    void processEvents();
    void update();
    void render();
    void displayEntities();
    void displayGameOver();
    const HorDirection& getInput() const { return horDirection; }
    void stop();
    void restart();

    void addEntityView(const std::shared_ptr<view::EntityView>& view);
    void removeEntityView(const std::shared_ptr<view::EntityView>& view);
};

#endif // DOODLEJUMP_GAME_H