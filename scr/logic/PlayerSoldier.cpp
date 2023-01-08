#include "PlayerSoldier.h"
#include <random>

PlayerSoldier::PlayerSoldier(float x, float y, float z) : Soldier(x, y, z) {
    setColor(glm::vec4(1));
    target = transform.getPosition();
}

void PlayerSoldier::setTarget(glm::vec3 target, int formationPos, int formationDim) {
    typedef std::mt19937 rng_type;
    std::uniform_int_distribution<rng_type::result_type> udist(0, unitPlaceHold);

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

void PlayerSoldier::moveTowarsTarget(float dt) {
    glm::vec3 vectorToTarget = target - transform.getPosition();
    float distance = glm::distance(target,transform.getPosition());
    distance == 0? distance = 0.00001 : distance = distance;
    vectorToTarget = vectorToTarget / distance;
    transform.setPosition(transform.getPosition() + vectorToTarget * (Soldier::getSpeed() * dt));

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);
}

void PlayerSoldier::update(float dt) {
    moveTowarsTarget(dt);
}
