#ifndef DOODLEJUMP_PLATFORMMANAGER_H
#define DOODLEJUMP_PLATFORMMANAGER_H

#include "Entities/Platform.h"
#include <vector>
#include <memory>

namespace model {

/**
 * @brief Manages platform entities in the game.
 * Handles adding, updating, and removing platforms.
 */
class PlatformManager {
private:
    std::vector<std::shared_ptr<Platform>> platforms; ///< List of active platforms
    float maxPlatformHeight; ///< Maximum height for platform placement

public:
    /**
     * @brief Construct a PlatformManager with an initial max platform height.
     * @param startHeight Initial maximum platform height.
     */
    explicit PlatformManager(float startHeight = 800.0f);

    /**
     * @brief Add a platform to the manager.
     * @param platform Shared pointer to Platform.
     */
    void addPlatform(const std::shared_ptr<Platform>& platform);

    /**
     * @brief Update the positions of platforms and remove out-of-view platforms.
     * @param cameraY Y position of the camera.
     */
    void updatePlatforms(float cameraY);

    /**
     * @brief Get the list of platforms.
     * @return Const reference to vector of Platform shared pointers.
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Platform>>& getPlatforms() const { return platforms; }

    /**
     * @brief Get the maximum platform height.
     * @return Maximum platform height.
     */
    [[nodiscard]] float getMaxPlatformHeight() const { return maxPlatformHeight; }

    /**
     * @brief Set the maximum platform height.
     * @param height New maximum platform height.
     */
    void setMaxPlatformHeight(float height);

    /**
     * @brief Remove a platform by index.
     * @param index Index of the platform to remove.
     */
    void removePlatform(size_t index);
};

}

#endif // DOODLEJUMP_PLATFORMMANAGER_H