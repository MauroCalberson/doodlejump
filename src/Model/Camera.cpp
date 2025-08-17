#include "Camera.h"

namespace model {

// Set the camera's coordinates
    void Camera::setcoords(float newX, float newY) {
        x = newX;
        y = newY;
    }

// Normalize world coordinates to camera-relative coordinates
    std::pair<float, float> Camera::normalizeCoordinates(float worldX, float worldY) const {
        float normalizedX = worldX - x;
        float normalizedY = worldY - y;
        return {normalizedX, normalizedY};
    }

// Check if a world position is within the camera's view
    bool Camera::isInView(float &worldX, float &worldY) const {
        auto [normalizedX, normalizedY] = normalizeCoordinates(worldX, worldY);
        return normalizedX >= 0 && normalizedX <= CameraWidth &&
               normalizedY >= y - 300 && normalizedY <= CameraHeight;
    }

// Update the camera's position based on the player's Y position
    void Camera::updatePosition(float &playerY) {
        // Keep the player centered in the view
        if (playerY < y + 300) {
            y = playerY - 300;
        }
    }

}