#ifndef RTS_OPENGL_ENEMYSOLDIER_H
#define RTS_OPENGL_ENEMYSOLDIER_H

#include "Soldier.h"


class EnemySoldier : public Soldier{
private:
    enum State{
        wondering,
        attacking,
        retreating
    };
    glm::vec3 direction;

    State state = State::wondering;
    float wonderingDirChangeTime;
public:
    EnemySoldier(float x, float y, float z);

    void changeDirection();

    void wonder(float dt);

    void update(float dt) override;
};


#endif //RTS_OPENGL_ENEMYSOLDIER_H
