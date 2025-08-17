#include <memory>

#ifndef DOODLEJUMP_ENTITYTVIEW_H
#define DOODLEJUMP_ENTITYTVIEW_H
#include "../Model/Observer.h"
#include <SFML/Graphics.hpp>
enum EntityViewType {
    BGTile,
    Platform,
    Player,
    Bonus
};
namespace view {
class BonusView;
class PlatformView;
class PlayerView;
class BGTileView;
class EntityView : public Observer {
public:
    bool isActive = true;
    void update(float x, float y) override {
        // Update the sprite's position based on the entity's position
        sprite->setPosition(x - 64, y - 64); // offset for sprite
    }
    void onDestroy() override { isActive = false; }
    sf::Sprite getSprite() { return *sprite; }
    virtual EntityViewType getType() = 0;
    void setType(EntityViewType type) {
        this->type = type;
    }
protected:
    float x;
    float y;
    std::unique_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;
    EntityViewType type;
};
}
#endif // DOODLEJUMP_ENTITYTVIEW_H
