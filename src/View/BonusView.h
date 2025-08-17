#ifndef DOODLEJUMP_BONUSVIEW_H
#define DOODLEJUMP_BONUSVIEW_H

#include "EntitytView.h"
#include "../Model/Enums.h"
namespace view {
class BonusView : public EntityView {
public:
    BonusView() {
        texture = std::make_unique<sf::Texture>();
        sprite = std::make_unique<sf::Sprite>();
    }

    void setTexture(EntityType type) {
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
    EntityViewType getType() override { return EntityViewType::Bonus; }
};
}
#endif // DOODLEJUMP_BONUSVIEW_H