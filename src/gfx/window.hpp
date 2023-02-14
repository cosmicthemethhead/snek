#pragma once
#include <GLFW/glfw3.h>

#define while_open(win) while(!glfwWindowShouldClose(win.internal_win))

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

namespace gfx {
  struct Window {
    GLFWwindow* internal_win;
    void init(const char[]);
    void terminate();
  };
}
