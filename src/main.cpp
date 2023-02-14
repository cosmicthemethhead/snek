#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gfx/window.hpp>

int main() {
  if (!glfwInit()) {
    printf("error:glfw - failed to initialize\n");
    return -1;
  }

  // set some glfw/opengl settings
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the window
  gfx::Window win;
  win.init("snek");

  // load/error-log glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("error:glad - failed to initialize\n");
    return -1;
  }

  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // create the buffer objs
  unsigned int vao;
  {unsigned int vbo;

  // push the vertices into the vbo
  float vertices[9] = {
    -0.5f, -0.45f, 0.0f,
     0.5f, -0.45f, 0.0f,
     0.0f,  0.45f, 0.0f
  };

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(vertices),
      vertices,
      GL_STATIC_DRAW);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // create the shaders
  unsigned int vertex_shader;
  unsigned int fragment_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  // set the vertex data
  {const char *vertex_shader_src =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_pos;\n"
    "void main() {\n"
    "  gl_Position = vec4(a_pos, 1.0);\n"
    "}\0";
  glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);}

  // set the fragment data
  {const char *fragment_shader_src =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "  FragColor = vec4(1.0f, 0.52f, 0.52f, 1.0f);\n"
    "}\0";
  glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);}

  glCompileShader(vertex_shader);
  glCompileShader(fragment_shader);

  // error-log the vertex shader
  {int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    printf("error:shader:vertex - failed to compile\n%s\n", info_log);
  }}

  // error-log the fragment shader
  {int success;
  char info_log[512];
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    printf("error:shader:fragment - failed to compile\n%s\n", info_log);
  }}

  unsigned int shader_program;
  shader_program = glCreateProgram();

  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  {int success;
  char info_log[512];
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    printf("error:shader:program - failed to link\n%s\n", info_log);
  }}

  glUseProgram(shader_program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // main loop, runs while window is open
  while_open (win) {
    glfwPollEvents();

    // set bg colour
    glClearColor(1.0f, 0.76f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the triangle
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(win.internal_win);
  }

  // termination
  glDeleteShader(shader_program);
  win.terminate();
  glfwTerminate();

  return 0;
}
