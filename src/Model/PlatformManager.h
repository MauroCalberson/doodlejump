#ifndef DOODLEJUMP_PLATFORMMANAGER_H
#define DOODLEJUMP_PLATFORMMANAGER_H

#include "Entities/Platform.h"
#include <vector>
#include <memory>

class PlatformManager {
private:
    std::vector<std::shared_ptr<Platform>> platforms;
    float maxPlatformHeight;

public:
    explicit PlatformManager(float startHeight = 800.0f) : maxPlatformHeight(startHeight) {}

    void addPlatform(const std::shared_ptr<Platform>& platform) {
        platforms.push_back(platform);
    }

    void updatePlatforms(float cameraY) {
        for (auto it = platforms.begin(); it != platforms.end();) {
            auto platformCoords = (*it)->getcoords();
            if (platformCoords.second < cameraY - 300 || platformCoords.second > cameraY + 950) {
                (*it)->notifyDeletion();
                it = platforms.erase(it);
            } else {
                (*it)->updatePosition();
                ++it;
            }
        }
    }

    const std::vector<std::shared_ptr<Platform>>& getPlatforms() const {
        return platforms;
    }

    float getMaxPlatformHeight() const { return maxPlatformHeight; }
    void setMaxPlatformHeight(float height) { maxPlatformHeight = height; }

    void removePlatform(size_t index) {
        if (index < platforms.size()) {
            platforms[index]->notifyDeletion();
            platforms.erase(platforms.begin() + index);
        }
    }

};

#endif // DOODLEJUMP_PLATFORMMANAGER_H