
#ifndef DOODLEJUMP_PLAYERVIEW_H
#define DOODLEJUMP_PLAYERVIEW_H
#include <SFML/Graphics.hpp>
#include "EntitytView.h"
class PlayerView : public EntityView {
public:
    PlayerView();
    void setTexture() {texture.loadFromFile("textures/doodleplayer.png"); sprite.setTexture(texture);};
    void update(float x, float y) override {
        // Update the sprite's position based on the platform's position
        sprite.setPosition(x, y);
    }
};

#endif // DOODLEJUMP_PLAYERVIEW_H
