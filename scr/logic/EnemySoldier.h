#ifndef RTS_OPENGL_ENEMYSOLDIER_H
#define RTS_OPENGL_ENEMYSOLDIER_H

#include "Soldier.h"

enum State{
    wondering,
    attacking,
    chasing
};
class PlayerSoldier;
class EnemySoldier : public Soldier{
private:
    glm::vec3 direction;
    PlayerSoldier * playerTarget;

    State state = State::wondering;

    float wonderingDirChangeTime;
    float stateChangeTime;
    float attackColorChangeTimer;

    bool dead = false;
public:
    EnemySoldier(float x, float y, float z);

    void setState(State state);
    void setPlayerTarget(PlayerSoldier * target);

    // retreat -1 wonder +1
    void changeDirection(int dir);

    void wonder(float dt);
    // kind of a retreat attack
    void attack(float dt);
    void moveToTarget(float dt);

    void update(float dt, const Grid & grid) override;
};


#endif //RTS_OPENGL_ENEMYSOLDIER_H
