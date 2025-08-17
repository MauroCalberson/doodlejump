#ifndef DOODLEJUMP_BONUSMANAGER_H
#define DOODLEJUMP_BONUSMANAGER_H

#include "Entities/Bonus.h"
#include <vector>
#include <memory>

namespace model {

/**
 * @brief Manages bonus entities in the game.
 * Handles adding, updating, and removing bonuses.
 */
class BonusManager {
private:
    std::vector<std::shared_ptr<Bonus>> bonuses; ///< List of active bonuses

public:
    /**
     * @brief Add a bonus to the manager.
     * @param bonus Shared pointer to Bonus.
     */
    void addBonus(const std::shared_ptr<Bonus>& bonus);

    /**
     * @brief Update the positions of bonuses and remove out-of-view bonuses.
     * @param cameraY Y position of the camera.
     */
    void updateBonuses(float cameraY);

    /**
     * @brief Get the list of bonuses.
     * @return Const reference to vector of Bonus shared pointers.
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Bonus>>& getBonuses() const { return bonuses; }

    /**
     * @brief Remove a bonus by index.
     * @param index Index of the bonus to remove.
     */
    void removeBonus(size_t index);
};

}

#endif // DOODLEJUMP_BONUSMANAGER_H