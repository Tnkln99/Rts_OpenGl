#include "Camera.h"
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


const int Camera::CAMERA_DIST {90};

const glm::mat4 Camera::PROJ_MATRIX {glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f)};
glm::mat4 Camera::VIEW_MATRIX {glm::lookAt(glm::vec3(0,0,CAMERA_DIST), glm::vec3(0,0,CAMERA_DIST) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f))};
glm::vec3 Camera::CAMERA_POS(0,0,Camera::CAMERA_DIST);

Camera::Camera() {
    transform.setPosition(0,0,Camera::CAMERA_DIST);
}

void Camera::update(GLFWwindow * window, float dt) {
    float cameraSpeed = 15.0f * dt;

    glm::vec3 cameraPos = transform.getPosition();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(transform.getDirection(), glm::vec3(1.0f, 0.0f,  0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(transform.getDirection(), glm::vec3(1.0f, 0.0f,  0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(transform.getDirection(), glm::vec3(0.0f, 1.0f,  0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(transform.getDirection(), glm::vec3(0.0f, 1.0f,  0.0f))) * cameraSpeed;

    transform.setPosition(cameraPos);
    CAMERA_POS = cameraPos;

    VIEW_MATRIX = glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getDirection(), glm::vec3(0.0f, 1.0f,  0.0f));
}
