// PlatformView.h
#ifndef DOODLEJUMP_PLATFORMVIEW_H
#define DOODLEJUMP_PLATFORMVIEW_H

#include "EntitytView.h"
#include "SFML/Graphics.hpp"
#include "../Model/Enums.h"

class PlatformView : public EntityView {
public:
    PlatformView() = default;
    ~PlatformView() override = default;
    void setTexture(PlatformType type) {
        switch (type) {
            case Green:
                texture.loadFromFile("textures/platform1.png");
                break;
            case Blue:
                texture.loadFromFile("textures/platform2.png");
                break;
            case Yellow:
                texture.loadFromFile("textures/platform3.png");
                break;
            case White:
                texture.loadFromFile("textures/platform4.png");
                break;
        }
        sprite.setTexture(texture);
    }

    sf::Sprite& getSprite() { return sprite; }
};

#endif // DOODLEJUMP_PLATFORMVIEW_H