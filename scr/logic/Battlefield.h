#ifndef RTS_3D_BATTLEFIELD_H
#define RTS_3D_BATTLEFIELD_H


#include "GLFW/glfw3.h"
#include "Soldier.h"
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Battlefield {
private:
    std::vector<Soldier*> soldiers;
    std::vector<Soldier*> selectedSoldiers;

    glm::vec3 pressedPosL;
    glm::vec3 pressedPosR;
public:
    ~Battlefield();
    void load(GLFWwindow *window);

    const std::vector<Soldier*> & getSoldiers();

    void update(GLFWwindow *window, float dt);

    void mouseCallBack(GLFWwindow* window, int button, int action, int mods );
};


#endif //RTS_3D_BATTLEFIELD_H
