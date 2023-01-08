#ifndef RTS_3D_BATTLEFIELD_H
#define RTS_3D_BATTLEFIELD_H


#include "GLFW/glfw3.h"
#include "PlayerSoldier.h"
#include "EnemySoldier.h"
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Battlefield {
private:
    std::vector<PlayerSoldier*> playerSoldiers;
    std::vector<PlayerSoldier*> selectedSoldiers;

    // todo when enemy playerSoldiers are added dont forget to render them
    std::vector<EnemySoldier*> enemySoldiers;

    glm::vec3 pressedPosL;
    glm::vec3 pressedPosR;
public:
    ~Battlefield();
    void load(GLFWwindow *window);

    const std::vector<PlayerSoldier*> & getPlayerSoldiers();
    const std::vector<EnemySoldier*> & getEnemySoldiers();

    void update(GLFWwindow *window, float dt);

    void mouseCallBack(GLFWwindow* window, int button, int action, int mods );
};


#endif //RTS_3D_BATTLEFIELD_H
