#include "BonusView.h"

namespace view {

// Construct a BonusView and initialize its texture and sprite
BonusView::BonusView() {
    texture = std::make_unique<sf::Texture>();
    sprite = std::make_unique<sf::Sprite>();
}

// Set the texture based on the bonus type
void BonusView::setTexture(EntityType type) {
    if (type == EntityType::SPRING) {
        if (!texture->loadFromFile("textures/spring.png")) {
            throw std::runtime_error("Failed to load texture: textures/spring.png");
        }
    } else { // JETPACK
        if (!texture->loadFromFile("textures/jetpack.png")) {
            throw std::runtime_error("Failed to load texture: textures/jetpack.png");
        }
    }
    sprite->setTexture(*texture);
}

}