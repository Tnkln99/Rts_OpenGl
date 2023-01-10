#include "Const.h"
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


const int Const::CAMERA_DIST {100};

const glm::mat4 Const::PROJ_MATRIX {glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f)};
const glm::mat4 Const::VIEW_MATRIX {glm::lookAt(glm::vec3(0,0,CAMERA_DIST), glm::vec3(0,0,CAMERA_DIST) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f))};
const float Const::UNIT_ATTACK_RANGE{7.0f};
const float Const::ENEMY_UNIT_DETECTION_RANGE{UNIT_ATTACK_RANGE + 5};