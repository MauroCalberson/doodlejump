#ifndef DOODLEJUMP_PLAYERVIEW_H
#define DOODLEJUMP_PLAYERVIEW_H

#include <SFML/Graphics.hpp>
#include "EntitytView.h"
#include <memory>
#include <stdexcept>

namespace view {

/**
 * @brief View class for the player entity.
 * Handles texture loading, sprite setup, and position updates for the player.
 */
class PlayerView : public EntityView {
public:
    /**
     * @brief Construct a PlayerView and initialize its texture and sprite.
     * Throws std::runtime_error if texture loading fails.
     */
    PlayerView();

    /**
     * @brief Set the texture for the player sprite.
     * Throws std::runtime_error if texture loading fails.
     */
    void setTexture();

    /**
     * @brief Update the sprite's position based on the player's coordinates.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    void update(float x, float y) override;

    /**
     * @brief Get the type of this entity view.
     * @return EntityViewType::Player
     */
    EntityViewType getType() override;
};

}

#endif // DOODLEJUMP_PLAYERVIEW_H