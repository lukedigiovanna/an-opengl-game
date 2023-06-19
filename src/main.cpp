#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

#include "render/Window.h"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "render/Texture.h"
#include "render/meshes.h"
#include "render/textures.h"
#include "render/Camera.h"
#include "render/Light.h"
#include "render/LightHandler.h"

#include "game/WorldObject.h"

#include "utils/keyboard.h"
#include "utils/random.h"

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

    // DirectionalLight light(glm::vec3(-0.2f, -1.0f, -0.3f));

    LightHandler lights;
    PointLight light0(glm::vec3(-5.0f, 1.0f, -5.0f));
    PointLight light1(glm::vec3(5.0f, 1.0f, -5.0f));
    PointLight light2(glm::vec3(-5.0f, 1.0f, 5.0f));
    PointLight light3(glm::vec3(5.0f, 1.0f, 5.0f));

    PointLight light(glm::vec3(0.0f, 2.0f, 0.0f));

    light.setColor(glm::vec3(1.0, 0.2, 0.8));

    lights.add(light0);
    lights.add(light1);
    lights.add(light2);
    lights.add(light3);
    lights.add(light);

    textures::init();
    meshes::init();

    glEnable(GL_DEPTH_TEST);

    std::vector<WorldObject> roses;
    for (int i = 0; i < 50; i++) {
        roses.push_back(
            WorldObject(glm::vec3(randomf(-10.0f, 10.0f), 0.25f, randomf(-10.0f, 10.0f)), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(1.0f), textures::ROSE, meshes::SQUARE)
        );
    }

    while (!window.shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light.setColor(glm::vec3(sin(glfwGetTime()) * 0.5f + 0.5f, 0.1f, 0.8f));

        float r = glfwGetTime() * 30;
        light0.setPosition(glm::vec3(cos(glm::radians(r)) * 5.0f, 1.0f, sin(glm::radians(r)) * 5.0f));
        light1.setPosition(glm::vec3(cos(glm::radians(r + 90)) * 5.0f, 1.0f, sin(glm::radians(r + 90)) * 5.0f));
        light2.setPosition(glm::vec3(cos(glm::radians(r + 180)) * 5.0f, 1.0f, sin(glm::radians(r + 180)) * 5.0f));
        light3.setPosition(glm::vec3(cos(glm::radians(r + 270)) * 5.0f, 1.0f, sin(glm::radians(r + 270)) * 5.0f));

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

        lights.set(shader);

        shader.setVec3("viewPosition", camera.getPosition());

        Texture* texts[] = {textures::DIRT_BLOCK, textures::EMERALD_BLOCK};
        int idx = 0;

        shader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        for (float x = -10.0f; x <= 10.0f; x += 0.25f) {
            for (float z = -10.0f; z <= 10.0f; z += 0.25f) {
                glm::mat4 trans(1.0f);
                trans = glm::translate(trans, glm::vec3(x, -0.125f, z));
                trans = glm::scale(trans, glm::vec3(0.25f, 0.25f, 0.25f));
                shader.setMatrix4("model", trans);

                texts[idx]->bind();
                idx = (idx + 1) % 2;
                
                meshes::CUBE->render();
            }
        }

        for (WorldObject& rose : roses) {
            rose.render(shader);
        }


        // draw the light source
        lightShader.use();
        camera.setMatrices(lightShader);
        
        lights.render(lightShader);
        
        window.swapBuffers();

        glfwPollEvents();
    }

    // Clean up resources

    meshes::destroy();
    textures::destroy();

    return 0;
}
