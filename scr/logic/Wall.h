#ifndef RTS_OPENGL_WALL_H
#define RTS_OPENGL_WALL_H

#include "components/Transformable.h"
class Wall {
private:
    Transformable transform;
    const glm::vec4 color = glm::vec4(0.7,0.5,0.6,1.0);
public:
    Wall(float x, float y, float z);

    const Transformable & getTransformable();
    const glm::vec4 & getColor();
};


#endif //RTS_OPENGL_WALL_H
