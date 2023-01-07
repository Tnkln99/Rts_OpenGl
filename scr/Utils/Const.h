#ifndef RTS_OPENGL_CONST_H
#define RTS_OPENGL_CONST_H

#include <glm/mat4x4.hpp>

class Const {
public:
    static const int CAMERA_DIST;

    static const glm::mat4 PROJ_MATRIX;
    static const glm::mat4 VIEW_MATRIX;
};


#endif //RTS_OPENGL_CONST_H
