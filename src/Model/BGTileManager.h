//
// Created by mauro on 15/08/2025.
//

#ifndef DOODLEJUMP_BGTILEMANAGER_H
#define DOODLEJUMP_BGTILEMANAGER_H

#include "BGTileManager.h"
#include "Entities/BGTile.h"
#include <memory>
#include <vector>
#include "Camera.h"
class BGTileManager {
private:
    std::vector<std::shared_ptr<BGTile>> backgroundTiles;
    float highestTileY = 0.0f;
    const float tileHeight = 1024.0f;

public:
    void addTile(const std::shared_ptr<BGTile>& tile) {
        backgroundTiles.push_back(tile);
    }

    void updateTiles(const std::shared_ptr<Camera>& camera) {
        for (auto& tile : backgroundTiles) {
            auto tileCoords = tile->getcoords();
            auto normalizedCoords = camera->normalizeCoordinates(tileCoords.first, tileCoords.second);

            // Reposition tiles that move out of view
            if (normalizedCoords.second > 900) {
                highestTileY -= tileHeight;
                tile->setcoords(tileCoords.first, highestTileY);
            }

            // Notify observers of the updated position
            normalizedCoords = camera->normalizeCoordinates(tile->getcoords().first, tile->getcoords().second);
            tile->notifyObservers(normalizedCoords.first, normalizedCoords.second);
        }
    }

    void setHighestTileY(float y) { highestTileY = y; }
    float getHighestTileY() const { return highestTileY; }
    const std::vector<std::shared_ptr<BGTile>>& getBackgroundTiles() const {
        return backgroundTiles;
    }
};
#endif // DOODLEJUMP_BGTILEMANAGER_H
