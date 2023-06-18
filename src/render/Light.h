#ifndef H_LIGHT
#define H_LIGHT

#include <glm/glm.hpp>

#include "Shader.h"

class Light {
protected:
    glm::vec3 color;
    glm::vec4 vector;
private:
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;

    // If we implement light attenuation generally, we will need this
    // float constant;
    // float linear;
    // float quadratic;
public:
    Light(glm::vec4 vector, glm::vec3 color, float ambient, float diffuse, float specular);
    Light(glm::vec4 vector);
    ~Light();

    void render(const Shader& lightShaer) const;
    void set(const Shader& shader, int index) const;

    void setColor(glm::vec3 color);
};

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 color, float ambient, float diffuse, float specular);
    DirectionalLight(glm::vec3 direction);

    void setDirection(glm::vec3 direction);
};

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, glm::vec3 color, float ambient, float diffuse, float specular);
    PointLight(glm::vec3 position);

    void setPosition(glm::vec3 position);
};



#endif