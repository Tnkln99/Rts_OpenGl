#include "Grid.h"
#include "../../Utils/Utility.h"
#include <fstream>
#include <limits>

Grid::Grid() {
    this->sizeGrid = 100;
    for(int i = 0; i < this->sizeGrid; i ++){
        for(int j = 0; j < this->sizeGrid; j++){
            pair<int, vector<int>> tile;
            tile.first = i * this->sizeGrid + j;
            if(i != 0){
                tile.second.push_back((i-1) * this->sizeGrid + j);
            }
            if(j != 0){
                tile.second.push_back(i * this->sizeGrid + (j-1));
            }
            if(i != sizeGrid-1){
                tile.second.push_back((i+1) * this->sizeGrid + j);
            }
            if(j != sizeGrid-1){
                tile.second.push_back(i * this->sizeGrid + (j+1));
            }

            if(i != 0 && j != 0){
                tile.second.push_back((i-1) * this->sizeGrid + (j-1));
            }
            if(i != sizeGrid-1 && j != sizeGrid-1){
                tile.second.push_back((i+1) * this->sizeGrid + (j+1));
            }
            if(i != 0 && j != sizeGrid-1){
                tile.second.push_back((i-1) * this->sizeGrid + (j+1));
            }
            if(i != sizeGrid-1 && j != 0){
                tile.second.push_back((i+1) * this->sizeGrid + (j-1));
            }

            graph[tile.first] = tile.second;
        }
    }

    //calculateGCost(97,198);
    //calculateGCost(98,198);
    //calculateGCost(99,198);

    //calculateGCost(197,198);
    //calculateGCost(199,198);

    //calculateGCost(297,198);
    //calculateGCost(298,198);
    //calculateGCost(299,198);
    //printGrid();
}

Grid::Node Grid::lowestFCost(vector<Node> openNodes) {
    double fLowest = std::numeric_limits<double>::infinity();
    Node tmp{};
    for (auto & node : openNodes){
        if(node.fCost < fLowest){
            fLowest = node.fCost;
            tmp = node;
        }
    }
    return tmp;
}

Grid::Node * Grid::findNote(vector<Node> nodes, int index) {
    auto node = nodes.begin();
    for(;node != nodes.end(); node++){
        if((*node).index == index){
            return &(*node);
        }
    }
    return nullptr;
}

void Grid::eraseNodeIfExists(vector<Node> nodes, int index) {
    auto node = nodes.begin();
    for(;node != nodes.end(); node++){
        if((*node).index == index){
            nodes.erase(node);
        }
    }
}

int Grid::calculateGCost(int neighbourIndex, int currentIndex) {
    int neighbourI = neighbourIndex / sizeGrid;
    int currentI = currentIndex / sizeGrid;

    int neighbourJ = neighbourIndex % sizeGrid;
    int currentJ = neighbourIndex % sizeGrid;

    vec2 neighbour{neighbourI, neighbourJ};
    vec2 current{currentI, currentJ};

    std::cout<<"neighbour "<< neighbour.x << " : " << neighbour.y << " current: "<<current.x<<" : "<<current.y <<" distance "<< distance(neighbour, current) <<std::endl;
    return 0;
}

// this should not only add nodes but should update them too
void Grid::fillOpenNodes(Node currentNode, int neighbourIndex, std::vector<Node> & openNodes, int posStart, int posEnd) {
    Node * neighbourNode = findNote(openNodes, neighbourIndex);

    int gCost = calculateGCost(neighbourIndex, currentNode.index);
    int hCost = calculateHCost(posEnd, currentNode.index);

    // if neighbour node is already in open nodes
    if(neighbourNode != nullptr){
        neighbourNode->gCost = gCost;
        neighbourNode->hCost = hCost;
        neighbourNode->fCost = neighbourNode->gCost + neighbourNode->hCost;
    }
    // if neighbour is not in open node we will create it and add to open nodes.
    else
    {
        Node neighbour;
        neighbour.indexParent = currentNode.index;

        neighbour.index = neighbourIndex;
        neighbour.gCost = gCost;
        neighbour.hCost = hCost;
        neighbour.gCost = neighbour.gCost + neighbour.hCost;

        openNodes.push_back(neighbour);
    }

}

glm::vec3 Grid::findWayTo(glm::vec3 pos, glm::vec3 dest) {
    int posIndex = Utility::convertCoordinatesToIndex(pos, sizeGrid);
    int desIndex = Utility::convertCoordinatesToIndex(dest, sizeGrid);

    std::vector<Node> open;
    std::vector<Node> close;

    Node current;
    current.index = posIndex;
    current.gCost = 1000000;
    current.hCost = 1000000;
    current.fCost = 1000000;

    open.push_back(current);

    bool reached = false;

    while(!reached){
        current = lowestFCost(open);

        eraseNodeIfExists(open, current.index);

        close.push_back(current);

        if(current.index == desIndex){
            reached = true;
        }

        for(auto neighbour : graph[current.index])
        {
            bool isNeighbourExistsClose = findNote(close, neighbour);
            if(isNeighbourExistsClose){
                continue;
            }
            fillOpenNodes(current, neighbour, open, posIndex, desIndex);
        }
    }


    return glm::vec3();
}

void Grid::putWall(glm::vec3 pos) {
    int index = Utility::convertCoordinatesToIndex(pos, sizeGrid);
    for(auto & i : graph){
        auto it = std::find(i.second.begin(), i.second.end(), index);
        if(it != i.second.end())
            i.second.erase(it);
    }
}

void Grid::printGrid() {
    for(auto & i : graph){
        cout<< i.first << " : ";
        for (auto j : i.second){
            cout << j <<" ";
        }
        cout<<endl;
    }
}

const unordered_map<int, vector<int>> &Grid::getGraph() {
    return graph;
}

int Grid::calculateHCost(int desIndex, int currentIndex) {
    return 0;
}







