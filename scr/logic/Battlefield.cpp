#include "Battlefield.h"
#include "../Utils/CameraUtils.h"


void Battlefield::load(GLFWwindow *window) {
    int offset = 20;
    for(int i = 0; i < 10;i++){
        playerSoldiers.emplace_back(new PlayerSoldier(-60, offset, 0));
        offset -= 4;
    }
    //offset = 20;
    for(int i = 0; i < 10;i++){
        enemySoldiers.emplace_back(new EnemySoldier(60, -50, 0));
        //offset -= 4;
    }

    glfwSetWindowUserPointer( window, this );

    glfwSetMouseButtonCallback( window, []( GLFWwindow* window, int button, int action, int mods )
    {
        Battlefield* battlefield = static_cast<Battlefield*>( glfwGetWindowUserPointer( window ) );
        battlefield->mouseCallBack(window, button, action, mods);
    } );
}

Battlefield::~Battlefield() {
    for(auto & soldier : playerSoldiers){
        delete soldier;
    }
    for(auto & soldier : enemySoldiers){
        delete soldier;
    }
}

const std::vector<PlayerSoldier*> &Battlefield::getPlayerSoldiers() {
    return playerSoldiers;
}

const std::vector<EnemySoldier *> &Battlefield::getEnemySoldiers() {
    return enemySoldiers;
}

void Battlefield::update(GLFWwindow * window, float dt) {
    for(auto & playerSoldier : playerSoldiers){
        playerSoldier->update(dt);
    }
    for(auto & enemySoldier : enemySoldiers){
        enemySoldier->update(dt);
    }


    for(auto & playerSoldier : playerSoldiers){
        for(auto & enemySoldier : enemySoldiers){
            fight(playerSoldier, enemySoldier);
        }
    }
}

void Battlefield::fight(PlayerSoldier *pSoldier, EnemySoldier *eSoldier) {
    float distance = glm::distance(pSoldier->getTransformable().getPosition(), eSoldier->getTransformable().getPosition());

    // in here we simulate the fight if they are close enough
    if(distance < Const::UNIT_ATTACK_RANGE)
    {
        if(pSoldier->getCanAttack())
        {
            eSoldier->getHit();
            pSoldier->setCanAttack(false);
        }
        if(eSoldier->getCanAttack())
        {
            pSoldier->getHit();
            eSoldier->setCanAttack(false);
        }

        if(pSoldier->getLife()<=0){
            playerSoldiers.erase(std::remove(playerSoldiers.begin(), playerSoldiers.end(), pSoldier),
                                 playerSoldiers.end());
        }
        if(eSoldier->getLife()<=0){
            enemySoldiers.erase(std::remove(enemySoldiers.begin(), enemySoldiers.end(), eSoldier),
                                enemySoldiers.end());
        }
    }

    // to give AI's the closest player unit
    if (distance < Const::ENEMY_UNIT_DETECTION_RANGE)
    {

    }
}

void Battlefield::mouseCallBack(GLFWwindow* window, int button, int action, int mods ) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    glm::vec3 rayDir = CameraUtils::getCameraRay(window, mouseX, mouseY);
    glm::vec3  mouseWorldPos = CameraUtils::ScreenToWorldMousePos(window, rayDir);

    int index = 0;
    for (auto & selectedSoldier : selectedSoldiers) {
        int unitsAlongSide = floor(sqrt(selectedSoldiers.size()+2));
        int selectedSoldierIndex = index;
        index++;
        if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
            EnemySoldier * selectedEnemy = Helper::findClosestEnemyInRange(mouseWorldPos, enemySoldiers);
            if(selectedEnemy != nullptr){
                selectedSoldier->setEnemyTarget(selectedEnemy);
            }
            else{
                selectedSoldier->setEnemyTarget(nullptr);
                selectedSoldier->setMoveTarget(mouseWorldPos, selectedSoldierIndex, unitsAlongSide);
            }
        }
    }

    glm::vec3 releasePosL = pressedPosL;
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        pressedPosL = CameraUtils::ScreenToWorldMousePos(window,rayDir);
        releasePosL = pressedPosL;

        pressedPosR = glm::vec3(0);
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        releasePosL = CameraUtils::ScreenToWorldMousePos(window,rayDir);
        for (auto & selectedSoldier : selectedSoldiers) {
            selectedSoldier->setColor(glm::vec4(1));
        }
        selectedSoldiers.clear();
    }

    glm::vec3 releasePosR = pressedPosR;
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        pressedPosR = CameraUtils::ScreenToWorldMousePos(window, rayDir);
        releasePosR = pressedPosR;

        pressedPosL = glm::vec3(0);
        releasePosL = pressedPosL;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
        releasePosR = CameraUtils::ScreenToWorldMousePos(window,rayDir);
    }

    for (auto & soldier : playerSoldiers){
        auto soldierPos = soldier->getTransformable().getPosition();
        if(pressedPosL.x < soldierPos.x && pressedPosL.y > soldierPos.y && releasePosL.x > soldierPos.x && releasePosL.y < soldierPos.y){
            auto it = find(selectedSoldiers.begin(), selectedSoldiers.end(), soldier);
            if (it == selectedSoldiers.end()) {
                selectedSoldiers.emplace_back(soldier);
                soldier->setColor(glm::vec4(0));
            }
        }

        if(pressedPosR.x < soldierPos.x && pressedPosR.y > soldierPos.y && releasePosR.x > soldierPos.x && releasePosR.y < soldierPos.y){
            selectedSoldiers.erase(std::remove(selectedSoldiers.begin(), selectedSoldiers.end(), soldier),
                                    selectedSoldiers.end());
            soldier->setColor(glm::vec4(1));
        }
    }
    /*
    for(auto & soldier : playerSoldiers) {
        if (soldier->getCollider().intersect(glm::vec3(0, 0, Const::CAMERA_DIST), rayDir)) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                selectedSoldiers.emplace_back(soldier);
                soldier->setColor(glm::vec4(0));
            }
            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
                selectedSoldiers.erase(std::remove(selectedSoldiers.begin(), selectedSoldiers.end(), soldier),
                                       selectedSoldiers.end());
                soldier->setColor(glm::vec4(1));
            }
        }
    }
    */
}


