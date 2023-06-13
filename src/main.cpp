#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "render/Window.h"
#include "render/Shader.h"
#include "render/shapes.h"
#include "render/Shape.h"

int main()
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    Window* window = new Window("Game", 640, 480);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init_shapes();

    Shader* shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");


    shader->use();
    shader->setUniform2f("screenDimension", 640, 480);

    float r = 0;

    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float max = 6.28f;
        int idx = 0;
        Shape* shapes[] = {s_square, s_triangle, s_circle};
        for (float s = 0.0f; s < max; s += max / 20) {
            float f = s + r;

            shader->setUniform2f("position", std::cosf(f) * 200, std::sinf(f) * 200);
            shader->setUniform2f("dimension", s * 100 / max, s * 100 / max);
            shader->setUniform1f("rotation", f);
        
            shader->setUniform4f("color", 1.0 - (std::sinf(f) * 0.5f + 0.5f), std::cosf(f) * 0.5f + 0.5f, 1.0, 1.0);

            shapes[idx++]->draw();
            idx%=3;
        }


        r+=0.01f;

        
        window->swapBuffers();

        glfwPollEvents();
    }

    destroy_shapes();

    delete shader;
    delete window;

    return 0;
}
