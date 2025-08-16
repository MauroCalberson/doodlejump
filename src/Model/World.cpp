#include "World.h"
#include <fstream>
#include <sstream>

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
        if (iss >> key >> value) {
            if (key == "camera_x") {
                camera = std::make_shared<Camera>();
                camera->setcoords(value, 0.0f);
            } else if (key == "camera_y" && camera) {
                auto coords = camera->getPosition();
                camera->setcoords(coords.first, value);
            }
        }
    }
    configFile.close();
    setup();
}

void World::setup() {
    factory = std::make_unique<ConcreteFactory>();
    platformManager = std::make_unique<PlatformManager>();
    bonusManager = std::make_unique<BonusManager>();
    bgTileManager = std::make_unique<BGTileManager>();

    player = factory->createPlayer();
    std::pair<float,float> coords = {300.0f, 400.0f};
    player->setcoords(coords.first, coords.second);
    if (camera) {
        auto coords = camera->normalizeCoordinates(300.0f, 400.0f);
        player->notifyObservers(coords.first, coords.second);
    }

    createBackgroundTiles();

    // Initial platform generation
    while (platformManager->getMaxPlatformHeight() > 0) {
        auto platform = generatePlatform();
        platformManager->addPlatform(platform);
    }
}

void World::update() {
    if (!player->move(camera)) {
        Game::getInstance()->stop();
        return;
    }
    // Handle collisions
    float playerY = player->getcoords().second;
    handleCollisions(playerY);
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


void World::handleCollisions(float& newY) {
    auto collision = CollisionSystem::detectCollision(player, platformManager->getPlatforms(), bonusManager->getBonuses());

    if (collision.hasCollision) {
        auto entity = collision.collidedEntity;
        if (entity->getType() == EntityType::JETPACK) {
            player->setVerticalSpeed(100.0f);
            bonusManager->removeBonus(collision.index);
        } else if (entity->getType() == EntityType::SPRING) {
            player->setVerticalSpeed(56.509f);
            bonusManager->removeBonus(collision.index);
        } else {
            player->setVerticalSpeed(25.0f);
            if (entity->getType() == EntityType::White) {
                platformManager->removePlatform(collision.index);
            }
        }
    }
}

std::pair<float, float> World::calcPlatformCoords() {
    auto& random = Random::getInstance();
    float baseSpacing = 50.0f;
    float randVariation = random.getFloat(0.0f, 100.0f);
    float y = platformManager->getMaxPlatformHeight() - baseSpacing - (randVariation * difficulty) - 50 * difficulty;
    float x = random.getFloat(60.0f, 540.0f);
    platformManager->setMaxPlatformHeight(y);
    return {x, y};
}

std::shared_ptr<Platform> World::generatePlatform() {
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

void World::updateDifficulty() {
    auto cameraPos = camera->getPosition();
    float absHeight = std::max(0.0f, -cameraPos.second);
    difficulty = std::min(absHeight / 100000.0f, 1.0f);
}

void World::createBackgroundTiles() {
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
void World::notifyEntityObservers() {
    for(const auto& platform : platformManager->getPlatforms()) {
        auto coords = camera->normalizeCoordinates(platform->getcoords().first, platform->getcoords().second);
        platform->notifyObservers(coords.first, coords.second);
    }
    for(const auto& bonus : bonusManager->getBonuses()) {
        auto coords = camera->normalizeCoordinates(bonus->getcoords().first, bonus->getcoords().second);
        bonus->notifyObservers(coords.first, coords.second);
    }
    for(const auto& tile : bgTileManager->getBackgroundTiles()) {
        auto coords = camera->normalizeCoordinates(tile->getcoords().first, tile->getcoords().second);
        tile->notifyObservers(coords.first, coords.second);
    }
    auto playerCoords = camera->normalizeCoordinates(player->getcoords().first, player->getcoords().second);
    player->notifyObservers(playerCoords.first, playerCoords.second);
};