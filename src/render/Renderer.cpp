#include "Renderer.h"
#include "Shape.h"

Renderer::Renderer() {
    // initialize the shader
    this->shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");

}

Renderer::~Renderer() {
    delete this->shader;
}