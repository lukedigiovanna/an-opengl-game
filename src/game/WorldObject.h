#ifndef H_WORLD_OBJECT
#define H_WORLD_OBJECT

#include <glm/glm.hpp>

#include "../render/Shader.h"
#include "../render/Texture.h"
#include "../render/Mesh.h"

class WorldObject {
public:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 color;
    Texture* texture;
    Mesh* mesh;

    WorldObject(glm::vec3 position, glm::vec3 size, glm::vec3 color, Texture* texture, Mesh* mesh);
    
    void render(const Shader& shader) const;
};

#endif