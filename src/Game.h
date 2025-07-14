#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <SFML/Graphics.hpp>
#include "View/EntitytView.h"
#include "View/PlatformView.h"
#include "View/PlayerView.h"
#include "Model/World.h"
#include <iostream>
#include <vector>
#include <memory>

class Game {
private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
    std::vector<std::shared_ptr<EntityView>> EntityViews;

    Game() noexcept;

public:
    ~Game();

    static Game* getInstance() {
        static Game instance;
        return &instance;
    }

    void run();
    void processEvents();
    void update();
    void render();
    void displayEntities();

    // View management methods
    void addEntityView(std::shared_ptr<EntityView> view) {
        EntityViews.push_back(view);
    }
};

#endif // DOODLEJUMP_GAME_H