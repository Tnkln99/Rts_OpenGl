#include "EnemySoldier.h"
#include <GLFW/glfw3.h>
#include <random>

#include "PlayerSoldier.h"
#include "../Utils/Utility.h"

EnemySoldier::EnemySoldier(float x, float y, float z) : Soldier(x, y, z) {
    setColor(glm::vec4(0.3,0.4,0.5,1));
    baseColor = glm::vec4(0.3,0.4,0.5,1);

    wonderingDirChangeTime = glfwGetTime()-4;
    stateChangeTime = glfwGetTime()-1;
    attackColorChangeTimer = glfwGetTime()-1;
}

void EnemySoldier::setState(State state) {
    float currTime = glfwGetTime();
    if(currTime - stateChangeTime > 1.0f){
        this->state = state;
        stateChangeTime = currTime;
    }
}

void EnemySoldier::setPlayerTarget(PlayerSoldier *target) {
    playerTarget = target;
    //target->setColor(glm::vec4(0.3,0.2,0.5,1));
    attackFormation = Utility::generateRandomOffsetForPosition(0,unitPlaceHold);
}

void EnemySoldier::changeDirection(int dir)  {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> disX(0, dir * -1.0);
    std::uniform_real_distribution<> disY(0, dir * 1.0);

    float x = disX(gen);
    float y = disY(gen);

    direction = glm::vec3(x,y,0);
}

void EnemySoldier::wonder(float dt) {
    float currTime = glfwGetTime();
    if(currTime - wonderingDirChangeTime > 0.5f){
        changeDirection(1);
        wonderingDirChangeTime = currTime;
    }

    transform.setPosition(transform.getPosition() + direction * (Soldier::getSpeed() * dt));

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);
}

void EnemySoldier::attack(float dt) {

}

void EnemySoldier::moveToTarget(float dt) {
    if(playerTarget == nullptr){return;}
    glm::vec3 targetPos{0};
    targetPos.x = playerTarget->getTransformable().getPosition().x + attackFormation.x;
    targetPos.y = playerTarget->getTransformable().getPosition().y + attackFormation.y;
    glm::vec3 vectorToTarget = targetPos - transform.getPosition();
    float distance = glm::distance(targetPos, transform.getPosition());
    distance == 0? distance = 0.00001 : distance = distance;
    vectorToTarget = vectorToTarget / distance;
    transform.setPosition(transform.getPosition() + vectorToTarget * (Soldier::getSpeed() * dt));
}

void EnemySoldier::update(float dt, const Grid & grid) {
    Soldier::update(dt, grid);
    //std::cout<<to_string(state)<<std::endl;
    switch(this->state){
        case State::wondering:
            wonder(dt);
            break;
        case State::chasing:
            moveToTarget(dt);
            break;
        case State::attacking:
            attack(dt);
            break;
    }
}


