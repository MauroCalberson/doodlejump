#include "BGTileView.h"

namespace view {

// Construct a BGTileView and load its texture
    BGTileView::BGTileView() {
        texture = std::make_unique<sf::Texture>();
        sprite = std::make_unique<sf::Sprite>();
        if (!texture->loadFromFile("textures/background.png")) {
            throw std::runtime_error("Failed to load texture: textures/background.png");
        }
        sprite->setTexture(*texture);
    }

// Get the type of this entity view
    EntityViewType BGTileView::getType() {
        return EntityViewType::BGTile;
    }

}