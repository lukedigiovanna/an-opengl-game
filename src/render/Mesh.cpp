#include "Mesh.h"
#include <glad/glad.h>
#include "textures.h"

// Layout of each vertex is always
// [x][y][z] | [tx][ty]

#define NUM_ELEMENTS_PER_VERTEX 5
#define NUM_DIMENSIONS 3

Mesh::Mesh(float* vertexData, unsigned int* indices, unsigned int numVertices, unsigned int numTriangles) {
    this->numIndices = numTriangles * 3;

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);

    glBindVertexArray(this->vao);

    // set up vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_ELEMENTS_PER_VERTEX * numVertices, vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->numIndices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, NUM_DIMENSIONS, GL_FLOAT, GL_FALSE, NUM_ELEMENTS_PER_VERTEX * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, NUM_ELEMENTS_PER_VERTEX * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
}

void Mesh::render() const {
    GLint textureBinding;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &textureBinding);
    if (textureBinding == 0) {
        // bind the blank texture then
        textures::BLANK->bind();
    }
    // bind the vao
    glBindVertexArray(this->vao);
    // draw
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // unbind the vao
    glBindVertexArray(0);
}