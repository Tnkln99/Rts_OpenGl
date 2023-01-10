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
        // finds the closest enemy nearest to mouse click in PLAYER_UNIT_ATTACK_RANGE
        static EnemySoldier * findClosestEnemyInRange(glm::vec3 mousePos, const std::vector<EnemySoldier*>  & enemies){
            float nearestEnemyDist = Const::UNIT_ATTACK_RANGE;
            EnemySoldier * foundEnemy = nullptr;
            for(auto & enemy : enemies){
                float distance = glm::distance(enemy->getTransformable().getPosition(), mousePos);
                if(distance <= nearestEnemyDist){
                    foundEnemy = enemy;
                    nearestEnemyDist = distance;
                }
            }
            return foundEnemy;
        }
    };
    std::vector<PlayerSoldier*> playerSoldiers;
    std::vector<PlayerSoldier*> selectedSoldiers;

    std::vector<EnemySoldier*> enemySoldiers;

    glm::vec3 pressedPosL;
    glm::vec3 pressedPosR;
public:
    ~Battlefield();
    void load(GLFWwindow *window);

    const std::vector<PlayerSoldier*> & getPlayerSoldiers();
    const std::vector<EnemySoldier*> & getEnemySoldiers();

    // like a collider check looks if two soldiers are in a fight range if so makes the necessary arrangement
    void fight(PlayerSoldier * soldier1, EnemySoldier * soldier2);

    void update(GLFWwindow *window, float dt);

    void mouseCallBack(GLFWwindow* window, int button, int action, int mods );
};


#endif //RTS_3D_BATTLEFIELD_H
