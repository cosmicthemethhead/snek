#include "gfx/window.hpp"

#include <cstdio>
#include <iostream>
#include <GLFW/glfw3.h>

namespace gfx {
  void Window::init(const char title[]) {
    this->internal_win = glfwCreateWindow(800, 600, title, nullptr, nullptr);
    if (this->internal_win == nullptr) {
      printf("error:glfw:window - failed to initialize\n");
      glfwTerminate();
      exit(-1);
    }
  }

  void Window::terminate() {
    glfwDestroyWindow(this->internal_win);
  }
}
