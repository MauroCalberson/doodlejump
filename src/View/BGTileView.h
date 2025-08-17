#ifndef DOODLEJUMP_BGTILEVIEW_H
#define DOODLEJUMP_BGTILEVIEW_H

#include "EntitytView.h"
#include <memory>
#include <stdexcept>

namespace view {

/**
 * @brief View class for background tiles.
 * Handles texture loading and sprite setup for background tiles.
 */
class BGTileView : public EntityView {
public:
    /**
     * @brief Construct a BGTileView and load its texture.
     * Throws std::runtime_error if texture loading fails.
     */
    BGTileView();

    /**
     * @brief Get the type of this entity view.
     * @return EntityViewType::BGTile
     */
    EntityViewType getType() override;
};

}

#endif // DOODLEJUMP_BGTILEVIEW_H