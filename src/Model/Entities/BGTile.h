// src/Model/Entities/BGTile.h
#ifndef DOODLEJUMP_BGTILE_H
#define DOODLEJUMP_BGTILE_H

#include "Entitymodel.h"

class BGTile : public Entitymodel {
public:
    BGTile() = default;
    EntityType getType() const override {
        return EntityType::BGTILE;
    }
};

#endif // DOODLEJUMP_BGTILE_H