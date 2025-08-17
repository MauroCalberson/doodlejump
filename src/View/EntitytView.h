#ifndef DOODLEJUMP_ENTITYTVIEW_H
#define DOODLEJUMP_ENTITYTVIEW_H

#include <memory>
#include "../Model/Observer.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Enum for different entity view types.
 */
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

/**
 * @brief Base class for all entity views.
 * Handles sprite management and observer updates.
 */
class EntityView : public Observer {
public:
    bool isActive = true; ///< Indicates if the view is active

    /**
     * @brief Update the sprite's position based on the entity's position.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    void update(float x, float y) override;

    /**
     * @brief Mark the view as inactive when destroyed.
     */
    void onDestroy() override;

    /**
     * @brief Get the sprite for rendering.
     * @return Reference to the sprite.
     */
    sf::Sprite getSprite();

    /**
     * @brief Get the type of this entity view.
     * @return EntityViewType enum value.
     */
    virtual EntityViewType getType() = 0;

    /**
     * @brief Set the type of this entity view.
     * @param type EntityViewType enum value.
     */
    void setType(EntityViewType type);

protected:
    float x; ///< X position
    float y; ///< Y position
    std::unique_ptr<sf::Texture> texture; ///< Texture for the sprite
    std::unique_ptr<sf::Sprite> sprite;   ///< Sprite for rendering
    EntityViewType type; ///< Type of the entity view
};

}

#endif // DOODLEJUMP_ENTITYTVIEW_H