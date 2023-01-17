#include "Renderer.h"
#include "../logic/components/Camera.h"


void Renderer::loadRenderer(int windowWidth, int windowHeight) {
    shader.loadShaderFromFile("../shaders/default.vert","../shaders/default.frag","","","");
    selectionArea.loadShaderFromFile("../shaders/selectionArea.vert","../shaders/selectionArea.frag","","","");
    loadMesh();
    loadSelectionArea();
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

void Renderer::loadSelectionArea() {
    selectionAreaVertices.push_back(glm::vec3 {-1, -1,  1});//0
    selectionAreaVertices.push_back(glm::vec3 {1, -1,  1});//1
    selectionAreaVertices.push_back(glm::vec3 {-1,  1,  1});//2
    selectionAreaVertices.push_back(glm::vec3 {1,  1,  1});//3

    selectionAreaIndices = {
            0, 1, 3,
            0, 3, 2
    };

    GLuint EBO, VBO;
    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &selectionAreaVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(selectionAreaVAO);

    // Bind the VBO_N specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Introduce the positions into the VBO
    glBufferData(GL_ARRAY_BUFFER, selectionAreaVertices.size() * sizeof(glm::vec3), selectionAreaVertices.data(), GL_STATIC_DRAW);


    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, selectionAreaIndices.size() * sizeof(GLuint), selectionAreaIndices.data(), GL_STATIC_DRAW);


    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Renderer::forwardRender(Battlefield & bf) {
    shader.use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for(auto & soldier : bf.getPlayerSoldiers()){
        shader.setMatrix4("projection", Camera::PROJ_MATRIX);
        shader.setMatrix4("view", Camera::VIEW_MATRIX);
        shader.setMatrix4("transform", soldier->getTransformable().getMoveMatrix());

        shader.setVector4f("soldier_color", soldier->getColor());

        drawMesh();
    }

    for(auto & soldier : bf.getEnemySoldiers()){
        shader.setMatrix4("projection", Camera::PROJ_MATRIX);
        shader.setMatrix4("view", Camera::VIEW_MATRIX);
        shader.setMatrix4("transform", soldier->getTransformable().getMoveMatrix());

        shader.setVector4f("soldier_color", soldier->getColor());

        drawMesh();
    }

    for(auto & wall : bf.getWalls()){
        shader.setMatrix4("projection", Camera::PROJ_MATRIX);
        shader.setMatrix4("view", Camera::VIEW_MATRIX);
        shader.setMatrix4("transform", wall->getTransformable().getMoveMatrix());

        shader.setVector4f("soldier_color", wall->getColor());

        drawMesh();
    }


    if(bf.selectionArea.getIfMousePressed()){
        selectionArea.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        selectionArea.setMatrix4("projection", Camera::PROJ_MATRIX);
        selectionArea.setMatrix4("view", Camera::VIEW_MATRIX);
        selectionArea.setMatrix4("transform", bf.selectionArea.transform.getMoveMatrix());

        glBindVertexArray(selectionAreaVAO);
        glDrawElements(GL_TRIANGLES , selectionAreaIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

}

void Renderer::drawMesh() {
    glBindVertexArray(mesh.getId());
    glDrawElements(GL_TRIANGLES , mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
