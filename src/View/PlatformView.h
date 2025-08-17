#ifndef DOODLEJUMP_PLATFORMVIEW_H
#define DOODLEJUMP_PLATFORMVIEW_H

#include "EntitytView.h"
#include "SFML/Graphics.hpp"
#include "../Model/Enums.h"
#include <memory>
#include <stdexcept>

namespace view {

/**
 * @brief View class for platform entities.
 * Handles texture loading and sprite setup for platforms.
 */
    class PlatformView : public EntityView {
    public:
        /**
         * @brief Construct a PlatformView and initialize its texture and sprite.
         */
        PlatformView();

        /**
         * @brief Set the texture based on the platform type.
         * Throws std::runtime_error if texture loading fails.
         * @param type The type of platform entity.
         */
        void setTexture(EntityType type);

        /**
         * @brief Get the type of this entity view.
         * @return EntityViewType::Platform
         */
        [[nodiscard]] EntityViewType getType() override { return EntityViewType::Platform; }
    };

}

#endif // DOODLEJUMP_PLATFORMVIEW_H