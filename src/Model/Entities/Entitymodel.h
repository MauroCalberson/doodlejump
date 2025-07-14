

#ifndef DOODLEJUMP_ENTITYMODEL_H
#define DOODLEJUMP_ENTITYMODEL_H

#include "../../Helper/Random.h"
#include "Subject.h"
class Entitymodel : public Subject {
protected:
    float x;
    float y;

public:
    //Entitymodel() = default;
    void setcoords(float& x, float& y) override {
        this->x = x;
        this->y = y;
    }
    [[nodiscard]] std::pair<float, float> getcoords() const override {
        return {x, y};
    }
};


#endif // DOODLEJUMP_ENTITYMODEL_H
