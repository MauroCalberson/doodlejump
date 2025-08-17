#include "PlatformView.h"

namespace view {

// Construct a PlatformView and initialize its texture and sprite
    PlatformView::PlatformView() {
        texture = std::make_unique<sf::Texture>();
        sprite = std::make_unique<sf::Sprite>();
    }

// Set the texture based on the platform type
    void PlatformView::setTexture(EntityType type) {
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

}