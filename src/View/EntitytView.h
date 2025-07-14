

#ifndef DOODLEJUMP_ENTITYTVIEW_H
#define DOODLEJUMP_ENTITYTVIEW_H
#include "../Model/Observer.h"
#include <Graphics.hpp>
class EntityView : public Observer {
public:
    void update(float x, float y) override {
        // Update the sprite's position based on the entity's position
        sprite.setPosition(x, y);
    }
    sf::Sprite getSprite() {
        return sprite;
    }
protected:
    float x;
    float y;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // DOODLEJUMP_ENTITYTVIEW_H
