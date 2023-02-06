#include <cstdio>
#include <GLFW/glfw3.h>

#include <gfx/window.hpp>

int main() {
  if (!glfwInit()) {
    printf("error:glfw - failed to initialize\n");
    return -1;
  }

  // set some glfw/opengl settings
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  gfx::Window win;
  win.init("snek");

  // main loop, runs while window is open
  while_open (win) {
    glfwSwapBuffers(win.internal_win);
    glfwPollEvents();
  }

  // termination
  win.terminate();
  glfwTerminate();

  return 0;
}
