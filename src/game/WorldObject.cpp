#include "WorldObject.h"

#include <glm/gtc/matrix_transform.hpp>

WorldObject::WorldObject(glm::vec3 position, glm::vec3 size, glm::vec3 color, Texture* texture, Mesh* mesh)
    : position(position), size(size), color(color), texture(texture), mesh(mesh) {}

void WorldObject::render(const Shader& shader) const {
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, this->position);
    trans = glm::scale(trans, this->size);
    shader.setMatrix4("model", trans);

    shader.setVec3("color", this->color);

    this->texture->bind();
    this->mesh->render();
}