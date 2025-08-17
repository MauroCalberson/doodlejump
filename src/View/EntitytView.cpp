#include "EntitytView.h"

namespace view {

// Update the sprite's position based on the entity's position
void EntityView::update(float x, float y) {
    // Offset for sprite centering
    sprite->setPosition(x - 64, y - 64);
}

// Mark the view as inactive when destroyed
void EntityView::onDestroy() {
    isActive = false;
}

// Get the sprite for rendering
sf::Sprite EntityView::getSprite() {
    return *sprite;
}

// Set the type of this entity view
void EntityView::setType(EntityViewType type) {
    this->type = type;
}

}