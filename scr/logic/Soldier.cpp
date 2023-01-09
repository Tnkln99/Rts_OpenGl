#include "Soldier.h"


Soldier::Soldier(float x, float y, float z) {
    transform.setPosition(x,y,z);

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);
}

const Transformable &Soldier::getTransformable() {
    return transform;
}

const glm::vec4 &Soldier::getColor() {
    return color;
}

float Soldier::getSpeed() const {
    return speed;
}

CollisionBox & Soldier::getCollider() {
    return collisionBox;
}

[[maybe_unused]] int Soldier::getUnitPlaceHold() const {
    return unitPlaceHold;
}

void Soldier::setColor(glm::vec4 color) {
    this->color = color;
}

void Soldier::update(float dt) {

}
