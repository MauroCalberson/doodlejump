#ifndef DOODLEJUMP_BONUSVIEW_H
#define DOODLEJUMP_BONUSVIEW_H

#include "EntitytView.h"
#include "../Model/Enums.h"
#include <memory>
#include <stdexcept>

namespace view {

/**
 * @brief View class for bonus entities.
 * Handles texture loading and sprite setup for bonuses.
 */
class BonusView : public EntityView {
public:
    /**
     * @brief Construct a BonusView and initialize its texture and sprite.
     */
    BonusView();

    /**
     * @brief Set the texture based on the bonus type.
     * Throws std::runtime_error if texture loading fails.
     * @param type The type of bonus entity.
     */
    void setTexture(EntityType type);

    /**
     * @brief Get the type of this entity view.
     * @return EntityViewType::Bonus
     */
    EntityViewType getType() override { return EntityViewType::Bonus; }
};

}

#endif // DOODLEJUMP_BONUSVIEW_H