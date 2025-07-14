

#ifndef DOODLEJUMP_ENTITYCONTROLLER_H
#define DOODLEJUMP_ENTITYCONTROLLER_H
#include <Graphics.hpp>
#include <memory>
#include "../View/EntitytView.h"
#include "../Model/Entities/Entitymodel.h"
class EntityController {
    sf::Sprite sprite;
    std::shared_ptr<EntityView> view;
    std::shared_ptr<Entitymodel> model;
    void setSprite(sf::Sprite& s);
};

#endif // DOODLEJUMP_ENTITYCONTROLLER_H
