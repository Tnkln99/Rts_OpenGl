#ifndef RTS_3D_SOLDIER_H
#define RTS_3D_SOLDIER_H

#include "components/Transformable.h"
#include "components/CollisionBox.h"
#include <vector>


class Soldier {
private:
    bool canAttack = true;
    float speed = 15;
    glm::vec4 currentColor;

    float canAttackTimer;
    float colorChangeTimer;
protected:
    glm::vec4 baseColor;
    int life = 20;

    CollisionBox collisionBox;

    const int unitPlaceHold = 2;
    const int unitRankSpacing = unitPlaceHold * 3;

    Transformable transform;
    glm::vec3 attackFormation;
public:
    Soldier( float x, float y, float z);

    const Transformable & getTransformable();
    CollisionBox & getCollider();
    const glm::vec4 & getColor();
    [[nodiscard]] float getSpeed() const;
    [[nodiscard]] bool getCanAttack() const;
    int getLife() const;

    void getHit();

    [[nodiscard]] int getUnitPlaceHold() const;

    void setColor(glm::vec4 color);
    void setBaseColor(glm::vec4 color);
    void setCanAttack(bool canAttack);

    virtual void update(float dt);
};


#endif //RTS_3D_SOLDIER_H
