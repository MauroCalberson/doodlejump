//
// Created by mauro on 06/07/2025.
//
#include "EntitytView.h"
#ifndef DOODLEJUMP_BGTILEVIEW_H
#define DOODLEJUMP_BGTILEVIEW_H

class BGTileView : public EntityView {
public:
    BGTileView() {
        texture = std::make_unique<sf::Texture>();
        sprite = std::make_unique<sf::Sprite>();
        if (!texture->loadFromFile("textures/background.png")) {
            throw std::runtime_error("Failed to load texture: textures/background.png");
        }
        sprite->setTexture(*texture);
    }
};

#endif // DOODLEJUMP_BGTILEVIEW_H
