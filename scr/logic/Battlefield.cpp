#include "Battlefield.h"
#include "../Utils/CameraUtils.h"
#include "../Utils/Const.h"


void Battlefield::load() {
    for(int i = 0; i < 1;i++){
        soldiers.emplace_back(new Soldier(0,0,0));
    }
}

Battlefield::~Battlefield() {
    for(auto & soldier : soldiers){
        delete soldier;
    }
}

const std::vector<Soldier*> &Battlefield::getSoldiers() {
    return soldiers;
}

void Battlefield::update(GLFWwindow *window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    glm::vec3 rayDir = CameraUtils::getCameraRay(window, mouseX, mouseY);
    int mouseLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int mouseRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int mouseMiddle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3);


    int index = 0;
    for (auto & selectedSoldier : selectedSoldiers) {
        int unitsAlongSide = floor(sqrt(selectedSoldiers.size()+2));
        int selectedSoldierIndex = index;
        index++;
        std::cout<<index<<std::endl;
        if(mouseMiddle){
            selectedSoldier->setTarget(CameraUtils::ScreenToWorldMousePos(window,rayDir), selectedSoldierIndex, unitsAlongSide);
        }
    }

    for(auto & soldier : soldiers){

        if(soldier->getCollider().intersect(glm::vec3(0,0,Const::CAMERA_DIST), rayDir)){
            if(mouseLeft){
                selectedSoldiers.emplace_back(soldier);
                soldier->setColor(glm::vec4(0));
            }
            if(mouseRight){
                selectedSoldiers.erase(std::remove(selectedSoldiers.begin(), selectedSoldiers.end(), soldier), selectedSoldiers.end());
                soldier->setColor(glm::vec4(1));
            }
        }

        soldier->update();
    }
}




