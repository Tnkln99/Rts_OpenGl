#include "EnemySoldier.h"
#include <GLFW/glfw3.h>
#include <random>

EnemySoldier::EnemySoldier(float x, float y, float z) : Soldier(x, y, z) {
    setColor(glm::vec4(1,0,0,1));
    wonderingDirChangeTime = glfwGetTime()-4;
}

void EnemySoldier::changeDirection()  {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    float x = dis(gen);
    float y = dis(gen);

    direction = glm::vec3(x,y,0);
}

void EnemySoldier::wonder(float dt) {
    transform.setPosition(transform.getPosition() + direction * (Soldier::getSpeed() * dt));

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);
}

void EnemySoldier::update(float dt) {
    float currTime = glfwGetTime();
    if(currTime - wonderingDirChangeTime > 1.0f){
        changeDirection();
        wonderingDirChangeTime = currTime;
    }
    wonder(dt);
}

