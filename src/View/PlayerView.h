
#ifndef DOODLEJUMP_PLAYERVIEW_H
#define DOODLEJUMP_PLAYERVIEW_H
#include <SFML/Graphics.hpp>
#include "EntitytView.h"
namespace view {
class PlayerView : public EntityView {
public:
    PlayerView() {
        texture = std::make_unique<sf::Texture>();
        sprite = std::make_unique<sf::Sprite>();
        setTexture();
    }

    void setTexture() {
        if (texture->loadFromFile("textures/doodleplayer.png")) {
            sprite->setTexture(*texture);
        } else {
            throw std::runtime_error("Failed to load texture: textures/doodleplayer.png");
        }
    }

    void update(float x, float y) override { sprite->setPosition(x, y); }
    EntityViewType getType() override {
        return EntityViewType::Player;
    }
};
}
#endif // DOODLEJUMP_PLAYERVIEW_H
