#ifndef DOODLEJUMP_BONUSMANAGER_H
#define DOODLEJUMP_BONUSMANAGER_H

#include "Entities/Bonus.h"
#include <vector>
#include <memory>

class BonusManager {
private:
    std::vector<std::shared_ptr<Bonus>> bonuses;

public:
    void addBonus(const std::shared_ptr<Bonus>& bonus) {
        bonuses.push_back(bonus);
    }

    void updateBonuses(float cameraY) {
        for (auto it = bonuses.begin(); it != bonuses.end();) {
            (*it)->updatePosition();
            auto bonusCoords = (*it)->getcoords();
            if (bonusCoords.second < cameraY - 400 || bonusCoords.second > cameraY + 950) {
                (*it)->notifyDeletion();
                it = bonuses.erase(it);
            } else {
                ++it;
            }
        }
    }

    const std::vector<std::shared_ptr<Bonus>>& getBonuses() const {
        return bonuses;
    }

    void removeBonus(size_t index) {
        if (index < bonuses.size()) {
            bonuses[index]->notifyDeletion();
            bonuses.erase(bonuses.begin() + index);
        }
    }
};

#endif // DOODLEJUMP_BONUSMANAGER_H