

#ifndef DOODLEJUMP_ENUMS_H
#define DOODLEJUMP_ENUMS_H
enum VertDirection {
    UP,
    DOWN
};
enum HorDirection {
    LEFT,
    RIGHT,
    NONE
};
enum EntityType {
    Green,
    Yellow,
    Blue,
    White,
    PLAYER,
    BGTILE,
    SPRING,
    JETPACK
};
enum class BonusType {
    SPRING,
    JETPACK
};
#endif // DOODLEJUMP_ENUMS_H
