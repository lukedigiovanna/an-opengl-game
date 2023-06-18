#include "LightHandler.h"
#include <stdexcept>

LightHandler::LightHandler() {

}

void LightHandler::set(const Shader& shader) const {
    shader.setInt("numLights", this->lights.size());
    for (int i = 0; i < this->lights.size(); i++) {
        this->lights[i]->set(shader, i);
    }
}

void LightHandler::render(const Shader& shader) const {
    for (Light* light : lights) {
        light->render(shader);
    }
}

void LightHandler::add(Light& light) {
    if (this->lights.size() >= MAX_NUM_LIGHTS) {
        throw std::runtime_error("Maximum number of lights reached.");
    }

    this->lights.push_back(&light);
}

bool LightHandler::remove(const Light& light) {
    // auto found = std::find(lights.begin(), lights.end(), light);
    // bool success = found != lights.end();
    // lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
    // return success;
    return true;
}

void LightHandler::clear() {
    this->lights.clear();
}