#include "PlatformManager.h"

namespace model {

// Construct a PlatformManager with an initial max platform height
    PlatformManager::PlatformManager(float startHeight)
            : maxPlatformHeight(startHeight) {}

// Add a platform to the manager
    void PlatformManager::addPlatform(const std::shared_ptr <Platform> &platform) {
        platforms.push_back(platform);
    }

// Update the positions of platforms and remove out-of-view platforms
    void PlatformManager::updatePlatforms(float cameraY) {
        for (auto it = platforms.begin(); it != platforms.end();) {
            auto platformCoords = (*it)->getcoords();
            if (platformCoords.second < cameraY - 300 || platformCoords.second > cameraY + 850) {
                (*it)->notifyDeletion();
                it = platforms.erase(it);
            } else {
                (*it)->updatePosition();
                ++it;
            }
        }
    }

// Set the maximum platform height
    void PlatformManager::setMaxPlatformHeight(float height) {
        maxPlatformHeight = height;
    }

// Remove a platform by index
    void PlatformManager::removePlatform(size_t index) {
        if (index < platforms.size()) {
            platforms[index]->notifyDeletion();
            platforms.erase(platforms.begin() + index);
        }
    }

}