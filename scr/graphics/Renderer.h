#ifndef RTS_3D_RENDERER_H
#define RTS_3D_RENDERER_H


#include "Shader.h"
#include "../logic/Battlefield.h"
#include "Mesh.h"


class Renderer {
private:
    Shader shader;
    Shader selectionArea;
    Mesh mesh = Mesh('i');

    unsigned int selectionAreaVAO;
    std::vector<glm::vec3> selectionAreaVertices;
    std::vector<GLuint> selectionAreaIndices;
public:
    void loadRenderer(int windowWidth, int windowHeight);

    void loadMesh();
    void loadSelectionArea();

    void forwardRender(Battlefield & bf);

    void drawMesh();
};


#endif //RTS_3D_RENDERER_H
