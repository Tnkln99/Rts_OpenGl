#ifndef RTS_OPENGL_PLAYERSOLDIER_H
#define RTS_OPENGL_PLAYERSOLDIER_H

#include "Soldier.h"
#include "EnemySoldier.h"

class PlayerSoldier : public Soldier{
private:
    glm::vec3 posTarget;
    EnemySoldier * enemyToChase = nullptr;
public:
    PlayerSoldier(float x, float y, float z);

    void setMoveTarget(glm::vec3 target, int formationPos, int formationDim);
    void setEnemyTarget(EnemySoldier * enemyToChase);

    void moveTowarsTarget(float dt);

    void update(float dt) override;
};


#endif //RTS_OPENGL_PLAYERSOLDIER_H
