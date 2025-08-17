#include "PlayerView.h"

namespace view {

// Construct a PlayerView and initialize its texture and sprite
PlayerView::PlayerView() {
    texture = std::make_unique<sf::Texture>();
    sprite = std::make_unique<sf::Sprite>();
    setTexture();
}

// Set the texture for the player sprite
void PlayerView::setTexture() {
    if (texture->loadFromFile("textures/doodleplayer.png")) {
        sprite->setTexture(*texture);
    } else {
        throw std::runtime_error("Failed to load texture: textures/doodleplayer.png");
    }
}

// Update the sprite's position based on the player's coordinates
void PlayerView::update(float x, float y) {
    sprite->setPosition(x, y);
}

// Get the type of this entity view
EntityViewType PlayerView::getType() {
    return EntityViewType::Player;
}

}