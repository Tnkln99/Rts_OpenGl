#ifndef RTS_OPENGL_CAMERAUTILS_H
#define RTS_OPENGL_CAMERAUTILS_H

#include "GLFW/glfw3.h"
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;
using namespace glm;

class CameraUtils {
public:
    static glm::vec3 getCameraRay(GLFWwindow*window, double pixelX, double pixelY);
    static glm::vec3 ScreenToWorldMousePos(GLFWwindow *window, glm::vec3 rayDir);
};


#endif //RTS_OPENGL_CAMERAUTILS_H
