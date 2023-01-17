#include "Battlefield.h"
#include "../Utils/Utility.h"


void Battlefield::load(GLFWwindow *window) {
    int offset = 20;
    for(int i = 0; i < 1;i++){
        playerSoldiers.emplace_back(new PlayerSoldier(-60, offset, 0));
        offset -= 4;
    }
    for(int i = 0; i < 0;i++){
        enemySoldiers.emplace_back(new EnemySoldier(60, -30, 0));
    }

    offset = 20;
    for(int i = 0; i < 10;i++){
        Walls.emplace_back(new Wall(0, offset, 0));
        offset --;
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

const std::vector<EnemySoldier*> &Battlefield::getEnemySoldiers() {
    return enemySoldiers;
}

const std::vector<Wall *> &Battlefield::getWalls() {
    return Walls;
}

void Battlefield::update(GLFWwindow * window, float dt) {
    camera.update(window,dt);
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    glm::vec3 rayDir = Utility::getCameraRay(window, mouseX, mouseY);
    glm::vec3 mouseWorldPos = Utility::ScreenToWorldMousePos(window, rayDir);

    if(selectionArea.getIfMousePressed()){
        float scaleX = glm::distance(mouseWorldPos.x , pressedPosL.x);
        float scaleY = glm::distance(mouseWorldPos.y , pressedPosL.y);

        //std::cout<<scaleX<<" : "<<scaleY<<std::endl;

        selectionArea.transform.setPosition(mouseWorldPos.x, mouseWorldPos.y, 0.0f);
        selectionArea.transform.scale(scaleX,scaleY,1);
    }



    for(auto & playerSoldier : playerSoldiers){
        playerSoldier->update(dt);
        //std::cout<<round(playerSoldier->getTransformable().getPosition().x)<< " : "<<round(playerSoldier->getTransformable().getPosition().y)<<std::endl;
        for(auto & wall : Walls){
            if(round(playerSoldier->getTransformable().getPosition().x) == wall->getTransformable().getPosition().x && round(playerSoldier->getTransformable().getPosition().y) == wall->getTransformable().getPosition().y){
                std::cout<<"on wall"<<std::endl;
            }
        }
    }
    for(auto & enemySoldier : enemySoldiers){
        enemySoldier->update(dt);
    }


    for(auto & playerSoldier : playerSoldiers){
        for(auto & enemySoldier : enemySoldiers){
            fight(playerSoldier, enemySoldier);
        }
    }

    if(playerSoldiers.empty()){
        for(auto & enemySoldier : enemySoldiers){
            enemySoldier->setState(State::wondering);
        }
    }
}

void Battlefield::fight(PlayerSoldier *pSoldier, EnemySoldier *eSoldier) {
    float distance = glm::distance(pSoldier->getTransformable().getPosition(), eSoldier->getTransformable().getPosition());
    // in here we simulate the fight if they are close enough
    if(distance < Const::UNIT_ATTACK_RANGE)
    {
        eSoldier->setState(State::attacking);
        eSoldier->setPlayerTarget(nullptr);
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
    else if (distance < Const::ENEMY_UNIT_DETECTION_RANGE)
    {
        eSoldier->setState(State::chasing);
        eSoldier->setPlayerTarget(pSoldier);
    }

    else
    {
        eSoldier->setState(State::wondering);
    }
}

void Battlefield::mouseCallBack(GLFWwindow* window, int button, int action, int mods ) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    glm::vec3 rayDir = Utility::getCameraRay(window, mouseX, mouseY);
    glm::vec3 mouseWorldPos = Utility::ScreenToWorldMousePos(window, rayDir);

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
        pressedPosL = Utility::ScreenToWorldMousePos(window, rayDir);
        releasePosL = pressedPosL;

        pressedPosR = glm::vec3(0);
        selectionArea.setMousePressed(true);
    }



    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        releasePosL = Utility::ScreenToWorldMousePos(window, rayDir);
        for (auto & selectedSoldier : selectedSoldiers) {
            selectedSoldier->setColor(glm::vec4(1));
            selectedSoldier->setBaseColor(glm::vec4(1));
        }
        selectedSoldiers.clear();
        selectionArea.clear();
        selectionArea.setMousePressed(false);
    }

    glm::vec3 releasePosR = pressedPosR;
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        pressedPosR = Utility::ScreenToWorldMousePos(window, rayDir);
        releasePosR = pressedPosR;

        pressedPosL = glm::vec3(0);
        releasePosL = pressedPosL;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
        releasePosR = Utility::ScreenToWorldMousePos(window, rayDir);
    }

    for (auto & soldier : playerSoldiers){
        auto soldierPos = soldier->getTransformable().getPosition();
        float distancePressedAndReleaseX = std::abs(pressedPosL.x - releasePosL.x);
        float distancePressedAndReleaseY = std::abs(pressedPosL.y - releasePosL.y);
        if(pressedPosL.x < soldierPos.x && pressedPosL.y > soldierPos.y && releasePosL.x + distancePressedAndReleaseX > soldierPos.x && releasePosL.y - distancePressedAndReleaseY < soldierPos.y){
            auto it = find(selectedSoldiers.begin(), selectedSoldiers.end(), soldier);
            if (it == selectedSoldiers.end()) {
                selectedSoldiers.emplace_back(soldier);
                soldier->setColor(glm::vec4(0.5));
                soldier->setBaseColor(glm::vec4(0.5));
            }
        }

        if(pressedPosR.x < soldierPos.x && pressedPosR.y > soldierPos.y && releasePosR.x > soldierPos.x && releasePosR.y < soldierPos.y){
            selectedSoldiers.erase(std::remove(selectedSoldiers.begin(), selectedSoldiers.end(), soldier),
                                    selectedSoldiers.end());
            soldier->setColor(glm::vec4(1));
            soldier->setBaseColor(glm::vec4(1));
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


