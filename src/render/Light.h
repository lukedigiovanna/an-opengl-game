#ifndef H_LIGHT
#define H_LIGHT

#include <glm/glm.hpp>

#include "Shader.h"

class Light {
public:
    glm::vec3 color;
    glm::vec3 position;
    float ambientStrength;
    Light(glm::vec3 position, glm::vec3 color, float ambientStrength);
    ~Light();

    void render(const Shader& lightShaer) const;
};

#endif