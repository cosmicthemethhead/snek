#include <cstdio>
#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    printf("error:glfw - failed to initialize\n");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* wnd = glfwCreateWindow(800, 600, "snek", nullptr, nullptr);
  if (wnd == nullptr) {
    printf("error:glfw:window - failed to initialize\n");
    glfwTerminate();
    return -1;
  }

  while (!glfwWindowShouldClose(wnd)) {
    glfwSwapBuffers(wnd);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
