#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <SFML/Graphics.hpp>
#include "View/EntitytView.h"
#include "View/PlatformView.h"
#include "View/PlayerView.h"
#include "View/BonusView.h"
//#include "Model/World.h"
#include "View/BGTileView.h"
#include <memory>
#include <vector>
class World;
class Game {
private:
    sf::RenderWindow window;
    std::unique_ptr<World> world;
    sf::Font font;
    sf::Text scoreText;

    std::vector<std::shared_ptr<BGTileView>> bgTileViews;
    std::vector<std::shared_ptr<PlatformView>> platformViews;
    std::vector<std::shared_ptr<PlayerView>> playerViews;
    std::vector<std::shared_ptr<BonusView>> bonusViews;

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

    void addEntityView(std::shared_ptr<EntityView> view);
    void removeEntityView(const std::shared_ptr<EntityView>& view);
};

#endif // DOODLEJUMP_GAME_H