#include "Window.h"
#include "../utils/keyboard.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(std::string const& windowTitle, int width, int height) {
    this->window = glfwCreateWindow(width, height, windowTitle.data(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    setKeyCallback(this->window);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() const {
    glfwSwapBuffers(this->window);
}
