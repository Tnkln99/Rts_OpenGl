#include "CameraUtils.h"
#include "Const.h"



glm::vec3 CameraUtils::getCameraRay(GLFWwindow*window, double mouse_x, double mouse_y) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float x = (2.0f * mouse_x) / width - 1.0f;
    float y = 1.0f - (2.0f * mouse_y) / height;
    float z = 1.0f;
    vec3 ray_nds = vec3(x, y, z);

    vec4 ray_clip = vec4(vec2(ray_nds.x, ray_nds.y), -1.0, 1.0);

    vec4 ray_eye = inverse(Const::PROJ_MATRIX) * ray_clip;
    ray_eye = vec4(vec2(ray_eye.x,ray_eye.y), -1.0, 0.0);

    vec3 ray_wor = vec3(inverse(Const::VIEW_MATRIX) * ray_eye);
    ray_wor = normalize(ray_wor);

    return ray_wor;
}

glm::vec3 CameraUtils::ScreenToWorldMousePos(GLFWwindow *window, glm::vec3 rayDir) {
    glm::vec3 rayOrigin(0,0,Const::CAMERA_DIST);
    glm::vec3 planeOrigin(0,0,0);
    glm::vec3 planeNormal(0,0,1);

    float t = glm::dot(planeOrigin-rayOrigin, planeNormal) / glm::dot(rayDir,planeNormal);

    return rayOrigin + t*rayDir;
}

