#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "render/Window.h"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "render/Texture.h"
#include "render/meshes.h"
#include "render/textures.h"
#include "render/Camera.h"

#include "utils/keyboard.h"

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

    Window window = Window("Game", 640, 480);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader = Shader("shaders/vs.glsl", "shaders/fs.glsl");

    Camera camera;

    textures::init();
    meshes::init();

    shader.use();
    glEnable(GL_DEPTH_TEST);

    while (!window.shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 movement(0.0f);
        if (isKeyDown(GLFW_KEY_A)) {
            movement.x -= 1;
        }
        if (isKeyDown(GLFW_KEY_D)) {
            movement.x += 1;
        }
        if (isKeyDown(GLFW_KEY_W)) {
            movement.z += 1;
        }
        if (isKeyDown(GLFW_KEY_S)) {
            movement.z -= 1;
        }
        if (isKeyDown(GLFW_KEY_SPACE)) {
            movement.y += 1;
        }
        if (isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
            movement.y -= 1;
        }
        if (isKeyDown(GLFW_KEY_LEFT)) {
            camera.rotateYaw(-1.0f);
        }
        if (isKeyDown(GLFW_KEY_RIGHT)) {
            camera.rotateYaw(1.0f);
        }
        if (isKeyDown(GLFW_KEY_UP)) {
            camera.rotatePitch(1.0f);
        }
        if (isKeyDown(GLFW_KEY_DOWN)) {
            camera.rotatePitch(-1.0f);
        }
        float speed = 0.03f;
        movement = speed * movement;
        camera.move(movement);

        camera.setMatrices(shader);

        float r = glfwGetTime();

        shader.setUniform4f("color", 1.0, 1.0, 1.0, 1.0);
        Texture* texts[] = {textures::DIRT_BLOCK, textures::EMERALD_BLOCK};
        int idx = 0;
        for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
            for (float z = -10.0f; z <= 10.0f; z += 1.0f) {
                glm::mat4 trans(1.0f);
                trans = glm::translate(trans, glm::vec3(x, 0.0f, z));
                // trans = glm::rotate(trans, r, glm::vec3(0.0f, 1.0f, 0.0f));
                // trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
                shader.setUniformMatrix4fv("transform", trans);
                texts[idx]->bind();
                idx = (idx + 1) % 2;
                meshes::CUBE->render();
            }
        }
        
        window.swapBuffers();

        glfwPollEvents();
    }

    // Clean up resources

    meshes::destroy();
    textures::destroy();

    return 0;
}
