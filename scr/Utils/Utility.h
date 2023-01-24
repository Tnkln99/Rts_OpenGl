#ifndef RTS_OPENGL_UTILITY_H
#define RTS_OPENGL_UTILITY_H

#include "GLFW/glfw3.h"
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;
using namespace glm;

class Utility {
public:
    static glm::vec3 getCameraRay(GLFWwindow*window, double pixelX, double pixelY);
    static glm::vec3 ScreenToWorldMousePos(GLFWwindow *window, glm::vec3 rayDir);
    static glm::vec3 generateRandomOffsetForPosition(int min, int max);

    static int convertCoordinatesToIndex(glm::vec3 pos, int gridSize);
};


#endif //RTS_OPENGL_UTILITY_H
