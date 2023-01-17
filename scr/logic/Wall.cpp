#include "Wall.h"


Wall::Wall(float x, float y, float z) {
    transform.setPosition(x,y,z);
}

const Transformable &Wall::getTransformable() {
    return transform;
}

const glm::vec4 &Wall::getColor() {
    return color;
}

