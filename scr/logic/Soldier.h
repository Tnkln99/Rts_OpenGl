#ifndef RTS_3D_SOLDIER_H
#define RTS_3D_SOLDIER_H

#include "components/Transformable.h"
#include "components/CollisionBox.h"
#include <vector>


class Soldier {
private:
    float speed = 15;
    glm::vec4 color;
protected:
    CollisionBox collisionBox;

    const int unitPlaceHold = 2;
    const int unitRankSpacing = unitPlaceHold * 3;

    Transformable transform;
public:
    Soldier( float x, float y, float z);

    const Transformable & getTransformable();
    CollisionBox & getCollider();
    const glm::vec4 & getColor();
    [[nodiscard]] float getSpeed() const;

    [[nodiscard]] int getUnitPlaceHold() const;

    void setColor(glm::vec4 color);

    virtual void update(float dt);
};


#endif //RTS_3D_SOLDIER_H
