#include "Soldier.h"
#include <random>


Soldier::Soldier(float x, float y, float z) {
    transform.setPosition(x,y,z);
    target = transform.getPosition();

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

CollisionBox & Soldier::getCollider() {
    return collisionBox;
}

int Soldier::getUnitPlaceHold() const {
    return unitPlaceHold;
}

void Soldier::setColor(glm::vec4 color) {
    this->color = color;
}

void Soldier::setTarget(glm::vec3 target, int formationPos, int formationDim) {
    typedef std::mt19937 rng_type;
    std::uniform_int_distribution<rng_type::result_type> udist(0, 10);

    rng_type rng;

    rng_type::result_type const seedval = rand(); // get this from somewhere
    rng.seed(seedval);

    rng_type::result_type random_number1 = udist(rng);
    rng_type::result_type random_number2 = udist(rng);

    glm::vec3 randomOffSet(random_number1,random_number2,0);

    int colNum = formationPos % formationDim;
    int rowNum = floor(formationPos / formationDim);

    target.x += randomOffSet.x + colNum * unitRankSpacing;
    target.y += randomOffSet.y + rowNum * unitRankSpacing;

    this->target = target;
}

void Soldier::moveTowarsTarget() {
    glm::vec3 vectorToTarget = target - transform.getPosition();
    transform.setPosition(transform.getPosition() + vectorToTarget * speed);

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);
}

void Soldier::update() {
    moveTowarsTarget();
}
