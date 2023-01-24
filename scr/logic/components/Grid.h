#ifndef RTS_OPENGL_GRID_H
#define RTS_OPENGL_GRID_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <glm/glm.hpp>

using namespace std;

class Grid {
private:
    struct Node{
        int indexParent;
        int index;

        int gCost;
        int hCost;
        int fCost;
    };

    int sizeGrid;
    unordered_map<int, vector<int>> graph;

    // TODO:
    void fillOpenNodes(Node currentNode, int neighbourIndex, std::vector<Node> & openNodes, int posStart, int posEnd);    Node lowestFCost(std::vector<Node>);
    // returns the pointer of the node if it exists or will return null ptr
    Node * findNote(std::vector<Node> nodes, int index);
    void eraseNodeIfExists(std::vector<Node> nodes, int index);
    int calculateGCost(int neighbourIndex, int currentIndex);
    int calculateHCost(int desIndex, int currentIndex);
    // ----
public:
    Grid();
    const unordered_map<int, vector<int>> & getGraph();


    void putWall(glm::vec3 pos);
    // finds to way to the given coordinates with A* algo it will return the direction to do so
    glm::vec3 findWayTo(glm::vec3 pos, glm::vec3 dest);

    void printGrid();
};


#endif //RTS_OPENGL_GRID_H
