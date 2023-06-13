#ifndef H_WINDOW
#define H_WINDOW

#include <string>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* window;
public:
    Window(std::string const& windowTitle, int width, int height);
    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
};

#endif