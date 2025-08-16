#include "../../Game.h"
#include "Player.h"

bool Player::move(const std::shared_ptr<Camera>& camera) {
    if (isOffScreen(camera)) {
        return false;
    }

    handleHorizontalMovement();
    handleVerticalMovement();

    return true;
}

bool Player::isOffScreen(const std::shared_ptr<Camera>& camera) const {
    return camera->normalizeCoordinates(x, y).second > 800;
}

void Player::handleHorizontalMovement() {
    const auto& input = Game::getInstance()->getInput();
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

void Player::moveLeft() {
    x -= 7.5f;
    wrapAroundScreen();
}

void Player::moveRight() {
    x += 7.5f;
    wrapAroundScreen();
}

void Player::wrapAroundScreen() {
    if (x < -80) x = 540;
    if (x > 560) x = -80;
}

void Player::handleVerticalMovement() {
    applyGravity();
    updateVerticalPosition();
}

void Player::applyGravity() {
    verticalSpeed -= 1.0f;
}

void Player::updateVerticalPosition() {
    y -= verticalSpeed;
}