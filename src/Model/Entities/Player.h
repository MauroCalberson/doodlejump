

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H
#include "../Enums.h"
#include "Entitymodel.h"
class Player : public Entitymodel {
private:
    VertDirection vertdirection;
    HorDirection horDirection;
public:
    //Player() = default;
};


#endif //DOODLEJUMP_PLAYER_H
