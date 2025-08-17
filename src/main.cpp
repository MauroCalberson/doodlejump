#include "Model/World.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "View/ConcreteFactory.h"
#include "Game.h"

int main() {
    Game::getInstance()->run();
    return 0;
}