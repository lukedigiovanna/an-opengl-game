#include "keyboard.h"
#include <map>
#include <iostream>

static std::map<int, bool> keyPressed;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        // std::cout << "PRESS " << key << std::endl;
        keyPressed.insert_or_assign(key, true);
    }
    else if (action == GLFW_RELEASE) {
        // std::cout << "RELEASE " << key << std::endl;
        keyPressed.insert_or_assign(key, false);
    }
}

bool isKeyDown(int keycode) {
    auto found = keyPressed.find(keycode);
    if (found == keyPressed.end()) {
        return false;
    }
    else {
        return found->second;
    }
}

void setKeyCallback(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
}