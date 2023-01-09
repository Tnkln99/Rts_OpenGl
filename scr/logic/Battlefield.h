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
#include "../Utils/Const.h"
#include <random>

class Battlefield {
private:
    class Helper{
    private:
    public:
        // finds the closest enemy nearest to mouse click in UNIT_ATTACK_RANGE
        static EnemySoldier * findClosestEnemyInRange(glm::vec3 mousePos, const std::vector<EnemySoldier*>  & enemies){
            float nearestEnemyDist = Const::UNIT_ATTACK_RANGE;
            EnemySoldier * foundEnemy = nullptr;
            for(auto & enemy : enemies){
                enemy->setColor(glm::vec4(1,0,0,1));
                float distance = glm::distance(enemy->getTransformable().getPosition(), mousePos);
                if(distance <= nearestEnemyDist){
                    foundEnemy = enemy;
                    nearestEnemyDist = distance;
                }
            }
            if(foundEnemy!= nullptr){foundEnemy->setColor(glm::vec4(0.5,0.5,0.5,1));}
            return foundEnemy;
        }
    };
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
