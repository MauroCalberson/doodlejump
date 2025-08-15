// PlatformView.h
#ifndef DOODLEJUMP_PLATFORMVIEW_H
#define DOODLEJUMP_PLATFORMVIEW_H

#include "EntitytView.h"
#include "SFML/Graphics.hpp"
#include "../Model/Enums.h"

class PlatformView : public EntityView {
public:
    PlatformView() {
        texture = std::make_unique<sf::Texture>();
        sprite = std::make_unique<sf::Sprite>();
    }

    void setTexture(EntityType type) {
        switch (type) {
        case Green:
            if (!texture->loadFromFile("textures/platform1.png")) {
                throw std::runtime_error("Failed to load texture: textures/platform1.png");
            }
            break;
        case Blue:
            if (!texture->loadFromFile("textures/platform2.png")) {
                throw std::runtime_error("Failed to load texture: textures/platform2.png");
            }
            break;
        case Yellow:
            if (!texture->loadFromFile("textures/platform3.png")) {
                throw std::runtime_error("Failed to load texture: textures/platform3.png");
            }
            break;
        case White:
            if (!texture->loadFromFile("textures/platform4.png")) {
                throw std::runtime_error("Failed to load texture: textures/platform4.png");
            }
            break;
        }
        sprite->setTexture(*texture);
    }
};
#endif // DOODLEJUMP_PLATFORMVIEW_H