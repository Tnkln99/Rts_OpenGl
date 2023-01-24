#include "PlayerSoldier.h"
#include <random>
#include "../Utils/Const.h"
#include "../Utils/Utility.h"

#include "EnemySoldier.h"

PlayerSoldier::PlayerSoldier(float x, float y, float z) : Soldier(x, y, z) {
    setColor(glm::vec4(1));
    baseColor = glm::vec4(1);
    posTarget = transform.getPosition();
}

void PlayerSoldier::setMoveTarget(glm::vec3 target, int formationPos, int formationDim) {
    glm::vec3 randomOffSet = Utility::generateRandomOffsetForPosition(0,unitPlaceHold);

    int colNum = formationPos % formationDim;
    int rowNum = floor(formationPos / formationDim);

    target.x += randomOffSet.x + colNum * unitRankSpacing;
    target.y += randomOffSet.y + rowNum * unitRankSpacing;


    this->posTarget = target;
}

void PlayerSoldier::setEnemyTarget(EnemySoldier *enemyToChase) {
    this->enemyToChase = enemyToChase;
    attackFormation = Utility::generateRandomOffsetForPosition(0,Const::UNIT_ATTACK_RANGE);
}

void PlayerSoldier::moveTowarsTarget(float dt, const Grid & grid) {
    if(enemyToChase == nullptr){
        glm::vec3 vectorToTarget = posTarget - transform.getPosition();
        float distance = glm::distance(posTarget, transform.getPosition());
        distance == 0? distance = 0.00001 : distance = distance;
        vectorToTarget = vectorToTarget / distance;
        transform.setPosition(transform.getPosition() + vectorToTarget * (Soldier::getSpeed() * dt));
    }
    else{
        glm::vec3 targetPos{0};
        targetPos.x = enemyToChase->getTransformable().getPosition().x + attackFormation.x - Const::UNIT_ATTACK_RANGE/2;
        targetPos.y = enemyToChase->getTransformable().getPosition().y + attackFormation.y - Const::UNIT_ATTACK_RANGE/2;
        glm::vec3 vectorToTarget = targetPos - transform.getPosition();
        float distance = glm::distance(targetPos, transform.getPosition());
        distance == 0? distance = 0.00001 : distance = distance;
        vectorToTarget = vectorToTarget / distance;
        transform.setPosition(transform.getPosition() + vectorToTarget * (Soldier::getSpeed() * dt));
    }

    glm::vec3 maxInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(1));
    glm::vec3 minInit = glm::vec3(transform.getMoveMatrix() * glm::vec4(-1,-1,-1,1));
    collisionBox.setBounds(maxInit,minInit);
}

void PlayerSoldier::update(float dt, const Grid & grid) {
    Soldier::update(dt, grid);
    moveTowarsTarget(dt, grid);
}
