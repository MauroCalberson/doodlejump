// Platform.h
#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "Entitymodel.h"
#include "../Enums.h"

class Platform : public Entitymodel {

private:
    PlatformType type;

public:

    Platform() = default;
    ~Platform() override = default;
    void setType(PlatformType t) {
        type = t;
    }

    [[nodiscard]] PlatformType getType() const {
        return type;
    }

};

#endif // DOODLEJUMP_PLATFORM_H