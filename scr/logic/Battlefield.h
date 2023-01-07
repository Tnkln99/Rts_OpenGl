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
    int numberSelectedUnits = 0;
public:
    ~Battlefield();
    void load();

    const std::vector<Soldier*> & getSoldiers();

    void update(GLFWwindow *window);
};


#endif //RTS_3D_BATTLEFIELD_H
