#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <chrono>

#include "render/Window.h"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "render/Texture.h"
#include "render/meshes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

    Shader* shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
    Texture* texture = new Texture("resources/dirt.png");

    init_meshes();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

    shader->use();
    glEnable(GL_DEPTH_TEST);

    while (!window->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f + std::sinf(glfwGetTime())));

        float r = glfwGetTime();
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.0f));
        trans = glm::rotate(trans, r, glm::vec3(0.707f, 0.707f, 0));
        // trans = glm::scale(trans, glm::vec3(sr, sr, 1));
        // shader->setUniform4f("color", 1.0 - (std::sinf(r) * 0.5f + 0.5f), std::cosf(r) * 0.5f + 0.5f, 1.0, 1.0);
        shader->setUniform4f("color", 1.0, 1.0, 1.0, 1.0);
        shader->setUniformMatrix4fv("projection", projection);
        shader->setUniformMatrix4fv("view", view);
        shader->setUniformMatrix4fv("transform", trans);

        // texture->bind();
        m_circle->render();
        // texture->unbind();
        
        window->swapBuffers();

        glfwPollEvents();
    }

    destroy_meshes();

    delete shader;
    delete window;

    return 0;
}
