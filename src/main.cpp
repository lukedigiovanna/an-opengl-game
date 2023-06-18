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
#include "render/Light.h"

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
    Shader lightShader = Shader("shaders/lighting_vs.glsl", "shaders/lighting_fs.glsl");

    Camera camera;
    camera.setPosition(glm::vec3(0.0f, 2.0f, 0.0f));

    Light light(glm::vec3(3.0f, 4.0f, 0.0f), glm::vec3(1.0f,1.0f,1.0f), 0.1f);

    textures::init();
    meshes::init();

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

        shader.use();
        camera.setMatrices(shader);
        shader.setFloat("ambientStrength", light.ambientStrength);
        shader.setVec3("lightColor", light.color);
        shader.setVec3("lightPosition", light.position);

        shader.setVec3("viewPosition", camera.getPosition());

        Texture* texts[] = {textures::DIRT_BLOCK, textures::EMERALD_BLOCK};
        int idx = 0;

        shader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        for (float x = -10.0f; x <= 10.0f; x += 0.5f) {
            for (float z = -10.0f; z <= 10.0f; z += 0.5f) {
                glm::mat4 trans(1.0f);
                trans = glm::translate(trans, glm::vec3(x, sin(x) + cos(z), z));
                trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
                trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
                shader.setMatrix4("model", trans);

                texts[idx]->bind();
                idx = (idx + 1) % 2;
                
                meshes::CUBE->render();
            }
        }

        // draw the light source
        lightShader.use();
        camera.setMatrices(lightShader);
        light.render(lightShader);

        
        window.swapBuffers();

        glfwPollEvents();
    }

    // Clean up resources

    meshes::destroy();
    textures::destroy();

    return 0;
}



float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
