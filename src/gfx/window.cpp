#include "gfx/window.hpp"

#include <cstdio>
#include <iostream>
#include <GLFW/glfw3.h>

namespace gfx {
  void Window::init(const char title[]) {
    this->internal_win = glfwCreateWindow(
        WIN_WIDTH, WIN_HEIGHT,
        title, nullptr, nullptr);

    if (this->internal_win == nullptr) {
      printf("error:glfw:window - failed to initialize\n");
      glfwTerminate();
      exit(-1);
    }

    glfwMakeContextCurrent(this->internal_win);
  }

  void Window::terminate() {
    glfwDestroyWindow(this->internal_win);
  }
}
