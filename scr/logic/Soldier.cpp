#include "Soldier.h"
#include <GLFW/glfw3.h>


Soldier::Soldier(float x, float y, float z) {
    transform.setPosition(x,y,z);

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);

    canAttackTimer = glfwGetTime();
    colorChangeTimer = glfwGetTime();
}

const Transformable &Soldier::getTransformable() {
    return transform;
}

const glm::vec4 &Soldier::getColor() {
    return currentColor;
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

bool Soldier::getCanAttack() const {
    return canAttack;
}

void Soldier::setColor(glm::vec4 color) {
    this->currentColor = color;
}

void Soldier::setBaseColor(glm::vec4 color) {
    this->baseColor = color;
}

void Soldier::setCanAttack(bool canAttack) {
    this->canAttack = canAttack;
}

void Soldier::update(float dt) {
    float currTime = glfwGetTime();
    if(!canAttack){
        if(currTime - canAttackTimer > 1.0f){
            canAttack = true;
            canAttackTimer = currTime;
        }
    }

    if(currTime - colorChangeTimer > 2.0f){
        setColor(baseColor);
        colorChangeTimer = currTime;
    }
}

void Soldier::getHit() {
    glm::vec4 hitColor = glm::vec4(baseColor.x-0.2f, baseColor.y-0.2f, baseColor.z-0.2f,1);
    setColor(hitColor);
    life--;
}

int Soldier::getLife() const {
    return life;
}
