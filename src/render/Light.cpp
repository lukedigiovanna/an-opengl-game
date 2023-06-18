#include "Light.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

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

Light::Light(glm::vec4 vector, glm::vec3 color, float ambient, float diffuse, float specular) : 
    color(color), vector(vector), ambientStrength(ambient), diffuseStrength(diffuse), specularStrength(specular) {
    if (!builtLightMesh) {
        buildLightMesh();
    }
}

Light::Light(glm::vec4 vector) : Light(vector, glm::vec3(1.0f), 0.1f, 1.0f, 0.3f) {}

Light::~Light() {

}

void Light::render(const Shader& lightShader) const {
    if (this->vector.w == 0) {
        return; // don't render a directional light
    }
    // set up model uniform
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(this->vector));
    trans = glm::scale(trans, glm::vec3(0.5f,0.5f,0.5f));
    lightShader.setMatrix4("model", trans);

    lightShader.setVec3("color", color.x, color.y, color.z);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

void Light::set(const Shader& shader, int index) const {
    std::string name = "lights[" + std::to_string(index) + "]";
    shader.setVec4((name + ".vector").c_str(), this->vector);
    shader.setVec3((name + ".color").c_str(), this->color);
    shader.setFloat((name + ".ambient").c_str(), this->ambientStrength);
    shader.setFloat((name + ".diffuse").c_str(), this->diffuseStrength);
    shader.setFloat((name + ".specular").c_str(), this->specularStrength);
}

void Light::setColor(glm::vec3 color) {
    this->color = color;
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float ambient, float diffuse, float specular) 
    : Light(glm::vec4(direction, 0.0f), color, ambient, diffuse, specular) {}

DirectionalLight::DirectionalLight(glm::vec3 direction)
    : Light(glm::vec4(direction, 0.0f)) {}

void DirectionalLight::setDirection(glm::vec3 direction) {
    this->vector = glm::vec4(direction, 0.0f);
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float ambient, float diffuse, float specular) 
    : Light(glm::vec4(position, 1.0f), color, ambient, diffuse, specular) {}

PointLight::PointLight(glm::vec3 position)
    : Light(glm::vec4(position, 1.0f)) {}

void PointLight::setPosition(glm::vec3 position) {
    this->vector = glm::vec4(position, 1.0f);
}