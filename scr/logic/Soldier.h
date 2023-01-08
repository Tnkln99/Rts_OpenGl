#ifndef RTS_3D_SOLDIER_H
#define RTS_3D_SOLDIER_H

#include "components/Transformable.h"
#include "components/CollisionBox.h"
class Soldier {
private:
    float speed = 20;
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

    [[maybe_unused]] [[nodiscard]] int getUnitPlaceHold() const;

    void setColor(glm::vec4 color);

    virtual void update(float dt) = 0;
};


#endif //RTS_3D_SOLDIER_H
