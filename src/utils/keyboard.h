#ifndef H_KEYBOARD
#define H_KEYBOARD
#include <GLFW/glfw3.h>

bool isKeyDown(int keycode);
void setKeyCallback(GLFWwindow* window);

#endif