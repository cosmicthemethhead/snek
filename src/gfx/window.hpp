#pragma once
#include <GLFW/glfw3.h>

#define while_open(win) while(!glfwWindowShouldClose(win.internal_win))

namespace gfx {
  struct Window {
    GLFWwindow* internal_win;
    void init(const char[]);
    void terminate();
  };
}
