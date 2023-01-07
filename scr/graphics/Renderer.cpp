#include "Renderer.h"
#include "../Utils/Const.h"


void Renderer::loadRenderer(int windowWidth, int windowHeight) {
    shader.loadShaderFromFile("../shaders/default.vert","../shaders/default.frag","","","");
    loadMesh();
}


void Renderer::loadMesh() {
    GLuint EBO, VBO;
    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &mesh.getId());
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(mesh.getId());

    // Bind the VBO_N specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Introduce the positions into the VBO
    glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(Vertex), mesh.getVertices().data(), GL_STATIC_DRAW);


    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size() * sizeof(GLuint), mesh.getIndices().data(), GL_STATIC_DRAW);


    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::forwardRender(Battlefield & bf) {
    shader.use();
    for(auto & soldier : bf.getSoldiers()){
        shader.setMatrix4("projection", Const::PROJ_MATRIX);
        shader.setMatrix4("view", Const::VIEW_MATRIX);
        shader.setMatrix4("transform", soldier->getTransformable().getMoveMatrix());

        shader.setVector4f("soldier_color", soldier->getColor());

        drawMesh();
    }
}

void Renderer::drawMesh() {
    glBindVertexArray(mesh.getId());
    glDrawElements(GL_TRIANGLES , mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}



