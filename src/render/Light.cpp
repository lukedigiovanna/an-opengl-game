#include "Light.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,

    -0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,

    0.0f, -0.5f, -0.5f,
    0.0f, 0.5f, -0.5f, 
    0.0f, 0.5f, 0.5f,  

    0.0f, -0.5f, -0.5f,
    0.0f, 0.5f, 0.5f,
    0.0f, -0.5f, 0.5f,
};

static bool builtLightMesh = false;

static unsigned int vao;

// Builds a square mesh to use as a marker of a light source.
static void buildLightMesh() {
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    builtLightMesh = true;
}

Light::Light(glm::vec3 position, glm::vec3 color, float ambientStrength) : 
    color(color), position(position), ambientStrength(ambientStrength) {
    if (!builtLightMesh) {
        buildLightMesh();
    }
}

Light::~Light() {

}

void Light::render(const Shader& lightShader) const {
    // set up model uniform
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, this->position);
    trans = glm::scale(trans, glm::vec3(0.5f,0.5f,0.5f));
    lightShader.setMatrix4("model", trans);

    lightShader.setVec3("color", color.x, color.y, color.z);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}