#ifndef RTS_OPENGL_PLAYERSOLDIER_H
#define RTS_OPENGL_PLAYERSOLDIER_H

#include "Soldier.h"


class PlayerSoldier : public Soldier{
private:
    glm::vec3 target;
public:
    PlayerSoldier(float x, float y, float z);

    void setTarget(glm::vec3 target, int formationPos, int formationDim);

    void moveTowarsTarget(float dt);

    void update(float dt) override;
};


#endif //RTS_OPENGL_PLAYERSOLDIER_H
