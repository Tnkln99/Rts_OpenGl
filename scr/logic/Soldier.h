#ifndef RTS_3D_SOLDIER_H
#define RTS_3D_SOLDIER_H

#include "components/Transformable.h"
#include "components/CollisionBox.h"
class Soldier {
private:
    float speed = 0.0005;

    Transformable transform;
    CollisionBox collisionBox;
    glm::vec4 color = glm::vec4(1);

    glm::vec3 target;

    const int unitPlaceHold = 2;
    const int unitRankSpacing = unitPlaceHold * 3;
public:
    Soldier(float x, float y, float z);

    const Transformable & getTransformable();
    CollisionBox & getCollider();
    const glm::vec4 & getColor();
    [[nodiscard]] int getUnitPlaceHold() const;

    void setColor(glm::vec4 color);
    void setTarget(glm::vec3 target, int formationPos, int formationDim);

    void moveTowarsTarget();

    void update();
};


#endif //RTS_3D_SOLDIER_H
