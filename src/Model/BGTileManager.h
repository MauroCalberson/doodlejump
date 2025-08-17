#ifndef DOODLEJUMP_BGTILEMANAGER_H
#define DOODLEJUMP_BGTILEMANAGER_H

#include "Entities/BGTile.h"
#include <memory>
#include <vector>
#include "Camera.h"

namespace model {

/**
 * @brief Manages background tiles for the game.
 * Handles adding, updating, and repositioning tiles as needed.
 */
    class BGTileManager {
    private:
        std::vector <std::shared_ptr<BGTile>> backgroundTiles; ///< List of background tiles
        float highestTileY = 0.0f; ///< Y position of the highest tile
        const float tileHeight = 1024.0f; ///< Height of each tile

    public:
        /**
         * @brief Add a background tile to the manager.
         * @param tile Shared pointer to BGTile.
         */
        void addTile(const std::shared_ptr <BGTile> &tile);

        /**
         * @brief Update the positions of background tiles based on camera.
         * Repositions tiles that move out of view and notifies observers.
         * @param camera Shared pointer to Camera.
         */
        void updateTiles(const std::shared_ptr <Camera> &camera);

        /**
         * @brief Get the list of background tiles.
         * @return Const reference to vector of BGTile shared pointers.
         */
        [[nodiscard]] const std::vector <std::shared_ptr<BGTile>> &
        getBackgroundTiles() const { return backgroundTiles; }
    };

}

#endif // DOODLEJUMP_BGTILEMANAGER_H