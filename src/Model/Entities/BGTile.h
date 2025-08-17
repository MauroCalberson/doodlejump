// src/Model/Entities/BGTile.h
#ifndef DOODLEJUMP_BGTILE_H
#define DOODLEJUMP_BGTILE_H

#include "Entitymodel.h"
namespace model {
class BGTile : public Entitymodel {
public:
    BGTile() = default;
    [[nodiscard]] EntityType getType() const override { return EntityType::BGTILE; }
    float collidedwithPlayer() override {return 0.0f; } // No effect on player
};
}
#endif // DOODLEJUMP_BGTILE_H