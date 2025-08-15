#include <memory>

#ifndef DOODLEJUMP_ENTITYTVIEW_H
#define DOODLEJUMP_ENTITYTVIEW_H
#include "../Model/Observer.h"
#include <Graphics.hpp>
class EntityView : public Observer {
public:
    bool isActive = true;
    void update(float x, float y) override {
        // Update the sprite's position based on the entity's position
        sprite->setPosition(x-64, y-64); // offset for sprite
    }
    void onDestroy() override {
        isActive = false;
    }
    sf::Sprite getSprite() {
        return *sprite;
    }
protected:
    float x;
    float y;
    std::unique_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite>  sprite;
};

#endif // DOODLEJUMP_ENTITYTVIEW_H
