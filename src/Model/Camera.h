#ifndef DOODLEJUMP_CAMERA_H
#define DOODLEJUMP_CAMERA_H

#include <vector>
#include <utility>

namespace model {

/**
 * @brief Manages the camera's position and view in the game world.
 * Handles coordinate normalization and view checks.
 */
class Camera {
private:
    float x = 0;                  ///< Camera's X position
    float y = 0;                  ///< Camera's Y position
    float CameraWidth = 600;      ///< Width of the camera view
    float CameraHeight = 800;     ///< Height of the camera view

public:
    Camera() = default;

    /**
     * @brief Set the camera's coordinates.
     * @param newX New X position.
     * @param newY New Y position.
     */
    void setcoords(float newX, float newY);

    /**
     * @brief Get the camera's current position.
     * @return Pair of X and Y coordinates.
     */
    [[nodiscard]] std::pair<float, float> getPosition() const { return {x, y}; }

    /**
     * @brief Normalize world coordinates to camera-relative coordinates.
     * @param worldX World X position.
     * @param worldY World Y position.
     * @return Pair of normalized X and Y coordinates.
     */
    [[nodiscard]] std::pair<float, float> normalizeCoordinates(float worldX, float worldY) const;

    /**
     * @brief Check if a world position is within the camera's view.
     * @param worldX World X position (by reference).
     * @param worldY World Y position (by reference).
     * @return True if in view, false otherwise.
     */
    bool isInView(float& worldX, float& worldY) const;

    /**
     * @brief Update the camera's position based on the player's Y position.
     * @param playerY Player's Y position (by reference).
     */
    void updatePosition(float& playerY);
};

}

#endif // DOODLEJUMP_CAMERA_H