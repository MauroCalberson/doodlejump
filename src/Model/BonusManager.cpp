#include "BonusManager.h"

namespace model {

// Add a bonus to the manager
    void BonusManager::addBonus(const std::shared_ptr <Bonus> &bonus) {
        bonuses.push_back(bonus);
    }

// Update the positions of bonuses and remove out-of-view bonuses
    void BonusManager::updateBonuses(float cameraY) {
        for (auto it = bonuses.begin(); it != bonuses.end();) {
            (*it)->updateBonusPosition();
            auto bonusCoords = (*it)->getcoords();
            // Remove bonuses that are out of the visible range
            if (bonusCoords.second < cameraY - 400 || bonusCoords.second > cameraY + 850) {
                (*it)->notifyDeletion();
                it = bonuses.erase(it);
            } else {
                ++it;
            }
        }
    }

// Remove a bonus by index
    void BonusManager::removeBonus(size_t index) {
        if (index < bonuses.size()) {
            bonuses[index]->notifyDeletion();
            bonuses.erase(bonuses.begin() + index);
        }
    }

}