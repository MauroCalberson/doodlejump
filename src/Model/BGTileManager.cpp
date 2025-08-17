#include "BGTileManager.h"

namespace model {

// Add a background tile to the manager
    void BGTileManager::addTile(const std::shared_ptr <BGTile> &tile) {
        backgroundTiles.push_back(tile);
    }

// Update the positions of background tiles based on camera
    void BGTileManager::updateTiles(const std::shared_ptr <Camera> &camera) {
        for (auto &tile: backgroundTiles) {
            auto tileCoords = tile->getcoords();
            auto normalizedCoords = camera->normalizeCoordinates(tileCoords.first, tileCoords.second);

            // Reposition tiles that move out of view
            if (normalizedCoords.second > 900) {
                highestTileY -= tileHeight;
                tile->setcoords(tileCoords.first, highestTileY);
            }

            // Notify observers of the updated position
            auto tilecoords = tile->getcoords();
            normalizedCoords = camera->normalizeCoordinates(tilecoords.first, tilecoords.second);
            tile->notifyObservers(normalizedCoords.first, normalizedCoords.second);
        }
    }

}