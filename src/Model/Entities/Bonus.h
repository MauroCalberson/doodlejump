#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H
#include "Entitymodel.h"
#include "Platform.h"

namespace model {

/**
 * @brief Abstract base class for bonus entities attached to platforms.
 */
class Bonus : public Entitymodel {
protected:
    EntityType Type; ///< Type of the bonus
    std::weak_ptr<Platform> attachedPlatform; ///< Platform this bonus is attached to

public:
    /**
     * @brief Attach this bonus to a platform.
     * @param platform Shared pointer to the platform.
     */
    void attachToPlatform(const std::shared_ptr<Platform>& platform);

    /**
     * @brief Update the position of the bonus based on its platform.
     */
    virtual void updateBonusPosition() = 0;

    /**
     * @brief Handle collision with the player.
     * @return Effect value (e.g., bounce height or boost speed).
     */
    virtual float collidedwithPlayer() = 0;

    /**
     * @brief Get the hitbox of the bonus.
     * @return Hitbox struct.
     */
    [[nodiscard]] Hitbox getHitbox() const override = 0;
};

/**
 * @brief Spring bonus entity, gives player a bounce.
 */
class Spring : public Bonus {
private:
    float bounceHeight = 56.509f; ///< Bounce height for spring

public:
    Spring() = default;

    [[nodiscard]] float collidedwithPlayer() override;
    [[nodiscard]] EntityType getType() const override;
    void updateBonusPosition() override;
    [[nodiscard]] Hitbox getHitbox() const override;
};

/**
 * @brief Jetpack bonus entity, gives player a speed boost.
 */
class Jetpack : public Bonus {
private:
    float boostSpeed = 100.0f; ///< Boost speed for jetpack

public:
    Jetpack() = default;

    [[nodiscard]] float collidedwithPlayer() override;
    [[nodiscard]] EntityType getType() const override;
    void updateBonusPosition() override;
    [[nodiscard]] Hitbox getHitbox() const override;
};

}
#endif // DOODLEJUMP_BONUS_H