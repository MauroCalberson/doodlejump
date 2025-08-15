
#include "../Game.h"
#include "World.h"
#include <iostream>
#include <cmath>
//#include <chrono>
//#include <thread>
#include <fstream>
#include <sstream>
#include <random>


World::World(const std::string& configFilePath) {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        throw std::runtime_error("Failed to open config file: " + configFilePath);
    }
    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string key;
        float value;
        float defaultValue = 0.0f; // Default value for y coordinate when assigning x coordinate
        if (iss >> key >> value) {
            if (key == "camera_x") {
                camera = std::make_shared<Camera>();
                camera->setcoords(value,0); // Default y to 0.0f
            } else if (key == "camera_y") {
                if (camera) {
                    auto coords = camera->getPosition();
                    camera->setcoords(coords.first, value);
                }
            } else if (key == "player_y") {
                if (player) {
                    auto coords = player->getcoords();
                    player->setcoords(coords.first, value);
                }
            }
        }
    }

    configFile.close();
    setup();
}/*
World::World() {
    setup();
}*/

void World::setup() {
    //std::cout << Game::getInstance()->getPlayerView() << std::endl;
    factory = std::make_unique<ConcreteFactory>();
    //std::cout << Game::getInstance()->getPlayerView() << std::endl;

    player = factory->createPlayer();
    //std::cout << Game::getInstance()->getPlayerView() << std::endl;
    std::pair<float,float> coords = {300.0, 400.0};
    player->setcoords(coords.first, coords.second); // Default position for the player
    if (camera) {
        coords = camera->normalizeCoordinates(coords.first, coords.second); // Normalize coordinates based on camera position
    }
    player->notifyObservers(coords.first, coords.second); // Notify observers of the player's position

    createBackgroundTiles();


    do {
        std::shared_ptr<Platform> platform = generatePlatform();
        platforms.push_back(platform);
    } while (maxplatformheight > 0); // Example condition to generate platforms until they reach a certain height 800-68 because of sprite
    std::cout << platforms.size() << std::endl;

}

void World::update() {
    this->movePlayer();

    this->updateDifficulty();
    // Update platforms and other entities
    this->updateEntities();

}
void World::movePlayer() {
    auto playerCoords = player->getcoords();
    float playerVerticalSpeed = player->getVerticalSpeed();

    // Check if player has fallen too far down
    auto normPlayerCoords = camera->normalizeCoordinates(playerCoords.first, playerCoords.second);
    if (normPlayerCoords.second > 800) {
        Game::getInstance()->stop();
        return;
    }

    // Handle horizontal movement first
    const auto& input = Game::getInstance()->getInput();
    switch (input) {
    case HorDirection::LEFT:
        playerCoords.first -= 7.5;
        if (playerCoords.first < -80) {
            playerCoords.first = 540;
        }
        break;
    case HorDirection::RIGHT:
        playerCoords.first += 7.5;
        if (playerCoords.first > 560) {
            playerCoords.first = -80;
        }
        break;
    case HorDirection::NONE:
        break;
    }
    player->setcoords(playerCoords.first, playerCoords.second);

    // Update platform positions before collision detection
    for (auto& platform : platforms) {
        if (platform->getType() == EntityType::Blue || platform->getType() == EntityType::Yellow) {
            platform->updatePosition();
        }
    }


    // Then handle vertical movement and collisions
    player->setVerticalSpeed(playerVerticalSpeed - 1.0f);
    playerCoords.second -= playerVerticalSpeed;
    float newY = playerCoords.second;
    handleCollisions(newY);

    playerCoords.second = newY;

    player->setcoords(playerCoords.first, playerCoords.second);
    player->notifyObservers(normPlayerCoords.first, normPlayerCoords.second);

    // Camera update
    auto cameraCoords = camera->getPosition();
    if (playerCoords.second < cameraCoords.second + 300) {
        camera->setcoords(cameraCoords.first, playerCoords.second - 300);
    }
}
void World::updateDifficulty() {
    auto cameraPos = camera->getPosition();
    // Calculate difficulty based on camera height (y position)
    // Scale from 0.0 to 1.0 between 0 and 10000 height
    float absheight = std::max(0.0f, -cameraPos.second);
    difficulty = std::min(absheight / 100000.0f, 1.0f);
}

// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
// Helper function to check if two hitboxes intersect
bool doHitboxesIntersect(const Hitbox& a, const Hitbox& b) {
    return (a.x < b.x + b.width &&
            a.x + a.width > b.x &&
            a.y < b.y + b.height &&
            a.y + a.height > b.y);
}

CollisionInfo World::detectCollision() {
    auto playerHitbox = player->getHitbox();
    float verticalSpeed = player->getVerticalSpeed();
    // Check bonus collisions first
    int index = -1;
    for (const auto& bonus : bonuses) {
        index++;
        auto bonusHitbox = bonus->getHitbox();

        // Only detect collision with a spring if the player is moving downward
        if (bonus->getType() == EntityType::SPRING && verticalSpeed > 0) {
            continue;
        }

        if (doHitboxesIntersect(playerHitbox, bonusHitbox)) {
            return {true, bonus, index};
        }
    }
    // Only check when moving down
    if (verticalSpeed <= 0) {
        index = -1; // Reset index for platforms
        float startY = playerHitbox.y;
        float endY = startY - verticalSpeed;
        for (const auto& platform : platforms) {
            index++;
            auto platformHitbox = platform->getHitbox();
            float platformTop = platformHitbox.y;

            // Check horizontal alignment
            if (std::abs(playerHitbox.x - platformHitbox.x) < platformHitbox.width/2) {
                // Check if player will cross the platform during this frame
                if (startY + playerHitbox.height <= platformTop &&
                    endY + playerHitbox.height >= platformTop) {
                    std::cout << "Collision detected with platform at: "
                              << platform->getcoords().first << ", "
                              << platform->getcoords().second <<std::endl;
                    return {true, platform, index};
                }
            }
        }
    }
    return {false, nullptr};
}

void World::handleCollisions(float& newY) {
    CollisionInfo collision = detectCollision();

    if (collision.hasCollision) {
        // Get the platform that was hit
        auto Entity = collision.collidedEntity;
        // Handle platform type-specific behavior
        auto type = Entity->getType();
        if (type == EntityType::White) {
            // Notify observers before removing the platform
            Entity->notifyDeletion();
            // Remove the platform from the vector
            platforms.erase(platforms.begin() + collision.index);
            /*auto it = std::find(platforms.begin(), platforms.end(), Entity);
            if (it != platforms.end()) {
                platforms.erase(it);
            }*/
        }
        // Apply bonus effect
        if (type == EntityType::JETPACK) {
            std::cout << "Jetpack bonus collected!" << std::endl;
            player->setVerticalSpeed(100.0f); // Big boost
            Entity->notifyDeletion();
            auto it = std::find(bonuses.begin(), bonuses.end(), Entity);
            if (it != bonuses.end()) {
                bonuses.erase(it);
            }
            return;
        } else if (type == EntityType::SPRING) { // SPRING
            std::cout << "Spring bonus activated!" << std::endl;
            player->setVerticalSpeed(56.509f); // Medium 5x boost
            Entity->notifyDeletion();
            auto it = std::find(bonuses.begin(), bonuses.end(), Entity);
            if (it != bonuses.end()) {
                bonuses.erase(it);
            }
            return;
        }
        // Apply bounce effect
        player->setVerticalSpeed(25.0f); // Reset vertical speed for jump
    }
}
void World::updateEntities() {
    // Update platforms
    for (auto it = platforms.begin(); it != platforms.end();) {
        auto platformCoords = (*it)->getcoords();
        auto normalizedCoords = camera->normalizeCoordinates(platformCoords.first, platformCoords.second);

        if (normalizedCoords.second < -300 || normalizedCoords.second > 950) {
            (*it)->notifyDeletion();
            it = platforms.erase(it);
        } else {
            (*it)->notifyObservers(normalizedCoords.first, normalizedCoords.second);
            ++it;
        }
    }

    // Update background tiles
    const float tileHeight = 1024.0f;
    auto cameraPos = camera->getPosition();

    for (auto& tile : backgroundTiles) {
        auto tileCoords = tile->getcoords();
        auto normalizedCoords = camera->normalizeCoordinates(tileCoords.first, tileCoords.second);

        // If tile is below view, move it to top
        if (normalizedCoords.second > 900) {
            std::cout << "Tile below view, moving to top: " << tileCoords.first << ", " << tileCoords.second << std::endl;
            // Move current tile above highest tile
            //float newTileHeight = highestTileY - tileHeight;
            highestTileY -= tileHeight; // Update highest tile Y position
            tile->setcoords(tileCoords.first, highestTileY);
        }

        // Update tile view
        normalizedCoords = camera->normalizeCoordinates(tile->getcoords().first, tile->getcoords().second);
        tile->notifyObservers(normalizedCoords.first, normalizedCoords.second);
    }
    // Update bonuses
    for (auto it = bonuses.begin(); it != bonuses.end();) {
        (*it)->updatePosition(); // Update position if attached to moving platform

        auto bonusCoords = (*it)->getcoords();
        auto normalizedCoords = camera->normalizeCoordinates(bonusCoords.first, bonusCoords.second);

        if (normalizedCoords.second < -400 || normalizedCoords.second > 950) {
            (*it)->notifyDeletion();
            it = bonuses.erase(it);
        } else {
            (*it)->notifyObservers(normalizedCoords.first, normalizedCoords.second);
            ++it;
        }
    }

    // Generate new platforms
    while (maxplatformheight > cameraPos.second - 100) {
        std::shared_ptr<Platform> newPlatform = generatePlatform();
        platforms.push_back(newPlatform);
    }
}
std::pair<float, float> World::calcPlatformCoords() {
    // Calculate the y increment based on difficulty
    float base_spacing = 50.0f;
    float rand_variation = random.getFloat(0.0f, 100.0f); // Random variation for platform spacing
    float y = maxplatformheight - base_spacing - (rand_variation * difficulty) - 50 * difficulty; //basic y calculation according to difficulty
    float x = random.getFloat(60, 540); // Random x position within the window width (600-128, because sprite is 128x128) and there are 4 pixels of buffer on each side
    maxplatformheight = y;
    return {x,y};
}
std::shared_ptr<Platform> World::generatePlatform() {
    // Calculate spawn probabilities based on difficulty
    //CHANGEEEEE
    float specialPlatformChance = difficulty * 0.9f; // 0% at start, 90% at max difficulty
    float randomValue = random.getFloat(0.0f, 1.0f);

    EntityType platformType;
    if (randomValue < specialPlatformChance) {
        // Choose between special platform types
        float typeRoll = random.getFloat(0.0f, 1.0f);
        if (typeRoll < 0.4f) {
            platformType = EntityType::Blue;    // Moving platform
        } else if (typeRoll < 0.7f) {
            platformType = EntityType::Yellow;  // Breaking platform
        } else {
            platformType = EntityType::White;   // Disappearing platform
        }
    } else {
        platformType = EntityType::Green;       // Normal platform
    }

    std::shared_ptr<Platform> platform = factory->createPlatform(platformType);
    std::pair<float,float> coords = calcPlatformCoords();
    platform->setcoords(coords.first, coords.second);

    // Set movement bounds for special platforms
    if (platformType == EntityType::Yellow) {
        // Vertical movement bounds: 100 units up and down from spawn position
        platform->setMovementBounds(coords.second - 100, coords.second + 100);
    }
    else if (platformType == EntityType::Blue) {
        // Horizontal movement bounds: 100 units left and right from spawn position
        platform->setMovementBounds(coords.first - 100, coords.first + 100);
    }
    auto normalizedCoords = camera->normalizeCoordinates(coords.first, coords.second);
    platform->notifyObservers(normalizedCoords.first, normalizedCoords.second);
    // chance of creating a bonus, stops at max difficulty
    if (random.getFloat(0.0f, 1.0f) < 0.05f && difficulty != 1.0f) {
        // 30% chance for jetpack, 70% for spring
        EntityType Type = (random.getFloat(0.0f, 1.0f) < 0.3f) ?
                                                                   EntityType::JETPACK : EntityType::SPRING;
        auto bonus = factory->createBonus(Type);
        float adjustedY = coords.second - 20;
        bonus->setcoords(coords.first, adjustedY); // Position above platform
        bonus->attachToPlatform(platform);
        bonuses.push_back(bonus);
        normalizedCoords = camera->normalizeCoordinates(coords.first, coords.second);
        bonus->notifyObservers(normalizedCoords.first, normalizedCoords.second);
    }

    return platform;
}
std::pair<float,float> getStartPlayer() {
    // Default starting position for the player
    return {300.0f, 400.0f}; // x, y coordinates
}

void World::createBackgroundTiles() {
    // Create background tiles
    // Calculate the number of tiles needed based on screen dimensions
    const float tileXSize = 1024.0f; // Assuming tiles are 128x128 pixels
    const float tileYSize = 1024.0f; // Assuming tiles are 128x128 pixels
    const int tilesX = 1;          // Number of tiles horizontally (600/128 rounded up)
    const int tilesY = 2;          // Number of tiles vertically (800/128 rounded up)

    // Create grid of background tiles
    for (int y = 0; y < tilesY; ++y) {
        for (int x = 0; x < tilesX; ++x) {
            auto BGTile = factory->createBGTile();
            float tileX = x * tileXSize;
            float tileY = y * tileYSize;
            BGTile->setcoords(tileX, tileY);
            backgroundTiles.push_back(BGTile);

            // Normalize coordinates based on camera position and notify observers
            if (camera) {
                auto normalizedCoords = camera->normalizeCoordinates(tileX, tileY);
                BGTile->notifyObservers(normalizedCoords.first, normalizedCoords.second);
            }
        }
    }
}