#ifndef RTS_OPENGL_COLLISIONBOX_H
#define RTS_OPENGL_COLLISIONBOX_H

#include <iostream>
#include <glm/glm.hpp>

class CollisionBox {
private:
    std::pair<glm::vec3, glm::vec3> bounds;
public:
    CollisionBox() = default;

    void setBounds(const glm::vec3 & minBound, const glm::vec3 & maxBound);

    bool intersect(glm::vec3 rayOrigin, glm::vec3 rayDir);
};


#endif //RTS_OPENGL_COLLISIONBOX_H
