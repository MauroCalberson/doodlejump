
#include "../Game.h"
#include "World.h"
#include <iostream>
#include <chrono>
#include <thread>
World::World() {
    setup();
}

void World::setup() {
    //std::cout << Game::getInstance()->getPlayerView() << std::endl;
    std::shared_ptr<AbstractFactory> factory = std::make_shared<ConcreteFactory>();
    //std::cout << Game::getInstance()->getPlayerView() << std::endl;

    player = factory->createPlayer();
    //std::cout << Game::getInstance()->getPlayerView() << std::endl;

    for (int i = 0; i < 10; i++) {
        std::shared_ptr<Platform> platform = factory->createPlatform(PlatformType::Green);
        platforms.push_back(platform);
    }
    std::cout << platforms.size() << std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //update();
}
void World::update() {

}
