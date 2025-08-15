#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <SFML/Graphics.hpp>
#include "View/EntitytView.h"
#include "View/PlatformView.h"
#include "View/PlayerView.h"
//#include "View/BonusView.h"
#include "Model/World.h"
#include "View/BGTileView.h"
#include "View/BonusView.h"
#include <iostream>
#include <memory>
#include <vector>

class Game {
private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
    std::vector<std::shared_ptr<BGTileView>> bgTileViews;
    std::vector<std::shared_ptr<PlatformView>> platformViews;
    std::vector<std::shared_ptr<PlayerView>> playerViews;
    std::vector<std::shared_ptr<BonusView>> bonusViews;
    HorDirection horDirection = HorDirection::NONE;
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
    const HorDirection& getInput() const { return horDirection; }
    // View management methods
    void addEntityView(std::shared_ptr<EntityView> view) {
        if (auto bgTile = std::dynamic_pointer_cast<BGTileView>(view)) {
            bgTileViews.push_back(bgTile);
        }
        else if (auto platform = std::dynamic_pointer_cast<PlatformView>(view)) {
            platformViews.push_back(platform);
        }
        else if (auto player = std::dynamic_pointer_cast<PlayerView>(view)) {
            playerViews.push_back(player);
        }
        else if (auto bonus = std::dynamic_pointer_cast<BonusView>(view)) {
            bonusViews.push_back(bonus);
        }
    }
    void removeEntityView(const std::shared_ptr<EntityView>& view) {
        if (auto bgTile = std::dynamic_pointer_cast<BGTileView>(view)) {
            auto it = std::find(bgTileViews.begin(), bgTileViews.end(), bgTile);
            if (it != bgTileViews.end()) bgTileViews.erase(it);
        }
        else if (auto platform = std::dynamic_pointer_cast<PlatformView>(view)) {
            auto it = std::find(platformViews.begin(), platformViews.end(), platform);
            if (it != platformViews.end()) platformViews.erase(it);
        }
        else if (auto player = std::dynamic_pointer_cast<PlayerView>(view)) {
            auto it = std::find(playerViews.begin(), playerViews.end(), player);
            if (it != playerViews.end()) playerViews.erase(it);
        }
        else if (auto bonus = std::dynamic_pointer_cast<BonusView>(view)) {
            auto it = std::find(bonusViews.begin(), bonusViews.end(), bonus);
            if (it != bonusViews.end()) bonusViews.erase(it);
        }
    }
    void stop();
};

#endif // DOODLEJUMP_GAME_H