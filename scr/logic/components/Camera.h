#ifndef RTS_OPENGL_CAMERA_H
#define RTS_OPENGL_CAMERA_H

#include "Transformable.h"
#include "GLFW/glfw3.h"


class Camera {
private:
    Transformable transform;
public:
    static glm::vec3 CAMERA_POS;

    static const int CAMERA_DIST;

    static const glm::mat4 PROJ_MATRIX;
    static glm::mat4 VIEW_MATRIX;

    Camera();

    void update(GLFWwindow * window, float dt);
};


#endif //RTS_OPENGL_CAMERA_H
