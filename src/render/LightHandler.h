#ifndef H_LIGHT_HANDLER
#define H_LIGHT_HANDLER

#include "Light.h"
#include "Shader.h"

#define MAX_NUM_LIGHTS 8

#include <vector>

class LightHandler {
private:
    std::vector<Light*> lights;
public:
    LightHandler();

    // Sets the proper uniform values in the given shader
    void set(const Shader& shader) const;
    // Attempts to render each light in this handler
    void render(const Shader& shader) const;
    // Adds the given light to the handler
    void add(Light& light);
    // Returns whether or not the light was successfully removed
    bool remove(const Light& light);
    // Removes all lights from this handler
    void clear();
};

#endif