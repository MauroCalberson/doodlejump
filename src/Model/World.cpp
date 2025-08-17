#include "World.h"
#include <fstream>
#include <sstream>
#include "PlatformManager.h"
#include "BonusManager.h"
#include "BGTileManager.h"
#include <iostream>
model::World::World(std::unique_ptr<AbstractFactory> factory)
    : factory(std::move(factory)) {
    setup();
}

model::World::~World() = default;

void model::World::setup() {
    platformManager = std::make_unique<PlatformManager>();
    bonusManager = std::make_unique<BonusManager>();
    bgTileManager = std::make_unique<BGTileManager>();
    camera = std::make_shared<Camera>();
    player = factory->createPlayer();
    std::pair<float,float> pcoords = {300.0f, 400.0f};
    player->setcoords(pcoords.first, pcoords.second);
    if (camera) {
        auto coords = camera->normalizeCoordinates(pcoords.first, pcoords.second);
        player->notifyObservers(coords.first, coords.second);
    }

    createBackgroundTiles();

    // Initial platform generation
    while (platformManager->getMaxPlatformHeight() > 0) {
        auto platform = generatePlatform();
        platformManager->addPlatform(platform);
    }
}

void model::World::update() {
    if (!player->move(camera)) {
        stop = true; // Player has fallen off the screen
        return;
    }
    // Handle collisions
    float playerY = player->getcoords().second;
    handleCollisions();
    // Update camera if needed
    camera->updatePosition(playerY);

    updateDifficulty();
    platformManager->updatePlatforms(camera->getPosition().second);
    bonusManager->updateBonuses(camera->getPosition().second);
    bgTileManager->updateTiles(camera);

    // Platform generation
    while (platformManager->getMaxPlatformHeight() > camera->getPosition().second - 100) {
        auto platform = generatePlatform();
        platformManager->addPlatform(platform);
    }
    notifyEntityObservers();
    updateScore();
}


void model::World::handleCollisions() {
    auto collision = CollisionSystem::detectCollision(player, platformManager->getPlatforms(), bonusManager->getBonuses());
    if (collision.hasCollision) {
        auto entity = collision.collidedEntity;
        float verticalSpeed = entity->collidedwithPlayer();
        player->setVerticalSpeed(verticalSpeed);
        switch (entity->getType()) {
            case EntityType::White: {
                platformManager->removePlatform(collision.index);
                break;
            }
            case EntityType::JETPACK: {
                bonusManager->removeBonus(collision.index);
                break;
            }
            case EntityType::SPRING: {
                bonusManager->removeBonus(collision.index);
                break;
            }
        }
    }
}

std::pair<float, float> model::World::calcPlatformCoords() {
    auto& random = Random::getInstance();
    float baseSpacing = 50.0f;
    float randVariation = random.getFloat(0.0f, 100.0f);
    float y = platformManager->getMaxPlatformHeight() - baseSpacing - (randVariation * difficulty) - 50 * difficulty;
    float x = random.getFloat(60.0f, 540.0f);
    platformManager->setMaxPlatformHeight(y);
    return {x, y};
}

std::shared_ptr<model::Platform> model::World::generatePlatform() {
    auto& random = Random::getInstance();
    float specialPlatformChance = difficulty * 0.9f;
    float randomValue = random.getFloat(0.0f, 1.0f);

    EntityType platformType = EntityType::Green;
    if (randomValue < specialPlatformChance) {
        float typeRoll = random.getFloat(0.0f, 1.0f);
        if (typeRoll < 0.4f) platformType = EntityType::Blue;
        else if (typeRoll < 0.7f) platformType = EntityType::Yellow;
        else platformType = EntityType::White;
    }

    auto platform = factory->createPlatform(platformType);
    auto coords = calcPlatformCoords();
    platform->setcoords(coords.first, coords.second);

    if (platformType == EntityType::Yellow) {
        platform->setMovementBounds(coords.second - 100, coords.second + 100);
    } else if (platformType == EntityType::Blue) {
        platform->setMovementBounds(coords.first - 100, coords.first + 100);
    }

    // Bonus generation
    if (random.getFloat(0.0f, 1.0f) < 0.05f && difficulty != 1.0f) {
        EntityType bonusType = (random.getFloat(0.0f, 1.0f) < 0.3f) ? EntityType::JETPACK : EntityType::SPRING;
        auto bonus = factory->createBonus(bonusType);
        float adjustedY = coords.second - 20;
        bonus->setcoords(coords.first, adjustedY);
        bonus->attachToPlatform(platform);
        bonusManager->addBonus(bonus);
    }

    return platform;
}

void model::World::updateDifficulty() {
    auto cameraPos = camera->getPosition();
    float absHeight = std::max(0.0f, -cameraPos.second);
    difficulty = std::min(absHeight / 100000.0f, 1.0f);
}

void model::World::createBackgroundTiles() {
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 1; ++x) {
            auto tile = factory->createBGTile();
            float tileX = x * 1024.0f;
            float tileY = y * 1024.0f;
            tile->setcoords(tileX, tileY);
            bgTileManager->addTile(tile);
            if (camera) {
                auto normalizedCoords = camera->normalizeCoordinates(tileX, tileY);
                tile->notifyObservers(normalizedCoords.first, normalizedCoords.second);
            }
        }
    }
}
void model::World::notifyEntityObservers() {
    std::vector<std::shared_ptr<Entitymodel>> entities;

    // collect all entities
    entities.insert(entities.end(),platformManager->getPlatforms().begin(),platformManager->getPlatforms().end());

    entities.insert(entities.end(),bonusManager->getBonuses().begin(),bonusManager->getBonuses().end());

    entities.insert(entities.end(),bgTileManager->getBackgroundTiles().begin(),bgTileManager->getBackgroundTiles().end());

    entities.push_back(player);

    // Notify all observers
    for (const auto& entity : entities) {
        auto entitycoords = entity->getcoords();
        auto coords = camera->normalizeCoordinates(
            entitycoords.first,
            entitycoords.second
        );
        entity->notifyObservers(coords.first, coords.second);
    }
};