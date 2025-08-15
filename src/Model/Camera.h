// src/Model/Camera.h
#ifndef DOODLEJUMP_CAMERA_H
#define DOODLEJUMP_CAMERA_H
#include <vector>
#include <iostream>
class Camera {
private:
    float x; // Camera's X position
    float y; // Camera's Y position
    float CameraWidth = 600; // Width of the Camera View (e.g., 600)
    float CameraHeight = 800; // Height of the Camera View (e.g., 800)

public:
    Camera() = default;

    void setcoords(float newX, float newY) {
        x = newX;
        y = newY;
    }

    std::pair<float, float> getPosition() const {
        return {x, y};
    }

    std::pair<float, float> normalizeCoordinates(float worldX, float worldY) const {
        float normalizedX = worldX - x; // Relative to camera's X position
        float normalizedY = worldY - y; // Relative to camera's Y position
        return {normalizedX, normalizedY};
    }

    bool isInView(float worldX, float worldY) const {
        auto [normalizedX, normalizedY] = normalizeCoordinates(worldX, worldY);
        return normalizedX >= 0 && normalizedX <= CameraWidth &&
               normalizedY >= y - 300 && normalizedY <= CameraHeight;
    }
};

#endif // DOODLEJUMP_CAMERA_H