#include "../../Game.h"
#include "Player.h"

namespace model {

// Move the player based on input and camera position
    bool Player::move(const std::shared_ptr <Camera> &camera) {
        if (isOffScreen(camera)) {
            return false;
        }
        handleHorizontalMovement();
        handleVerticalMovement();
        return true;
    }

// Check if the player is off the visible screen
    bool Player::isOffScreen(const std::shared_ptr <Camera> &camera) const {
        return camera->normalizeCoordinates(x, y).second > 800;
    }

// Handle horizontal movement based on input
    void Player::handleHorizontalMovement() {
        const auto &input = Game::getInstance()->getInput();
        switch (input) {
            case HorDirection::LEFT:
                moveLeft();
                break;
            case HorDirection::RIGHT:
                moveRight();
                break;
            case HorDirection::NONE:
                break;
        }
    }

// Move the player left and wrap around screen if needed
    void Player::moveLeft() {
        x -= 7.5f;
        wrapAroundScreen();
    }

// Move the player right and wrap around screen if needed
    void Player::moveRight() {
        x += 7.5f;
        wrapAroundScreen();
    }

// Wrap the player around the screen horizontally
    void Player::wrapAroundScreen() {
        if (x < -80) x = 540;
        if (x > 560) x = -80;
    }

// Handle vertical movement (gravity and position)
    void Player::handleVerticalMovement() {
        applyGravity();
        updateVerticalPosition();
    }

// Apply gravity to the player
    void Player::applyGravity() {
        verticalSpeed -= 1.0f;
    }

// Update the player's vertical position
    void Player::updateVerticalPosition() {
        y -= verticalSpeed;
    }

// Get the hitbox of the player
    Hitbox Player::getHitbox() const {
        return {x, y + 100, 44, 8};
    }

// Set the vertical speed of the player
    void Player::setVerticalSpeed(float speed) {
        verticalSpeed = speed;
    }

// Get the current vertical speed of the player
    float Player::getVerticalSpeed() const {
        return verticalSpeed;
    }

// Get the type of the entity
    EntityType Player::getType() const {
        return EntityType::PLAYER;
    }

// Handle collision with the player
    float Player::collidedwithPlayer() {
        return verticalSpeed;
    }

}