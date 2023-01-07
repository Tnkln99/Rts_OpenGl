#ifndef RTS_3D_RENDERER_H
#define RTS_3D_RENDERER_H


#include "Shader.h"
#include "../logic/Battlefield.h"
#include "Mesh.h"


class Renderer {
private:
    Shader shader;
    Mesh mesh = Mesh('c');
public:
    void loadRenderer(int windowWidth, int windowHeight);

    void loadMesh();

    void forwardRender(Battlefield & bf);

    void drawMesh();
};


#endif //RTS_3D_RENDERER_H
