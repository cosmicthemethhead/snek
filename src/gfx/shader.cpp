#include "gfx/shader.hpp"

#include "gfx/gfx.h"
#include <cstdio>

namespace gfx {
  void Shader::compile(const char* vertex_src, const char* fragment_src) {
    unsigned int vertex_id, fragment_id;
    // create the shaders
    vertex_id = glCreateShader(GL_VERTEX_SHADER);
    fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    // set the shader data
    glShaderSource(vertex_id, 1, &vertex_src, nullptr);
    glShaderSource(fragment_id, 1, &fragment_src, nullptr);

    glCompileShader(vertex_id);
    glCompileShader(fragment_id);

    // error-log the vertex shader
    {int success;
    char info_log[512];
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(vertex_id, 512, nullptr, info_log);
      printf("error:shader:vertex - failed to compile\n%s\n", info_log);
    }}

    // error-log the fragment shader
    {int success;
    char info_log[512];
    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(fragment_id, 512, nullptr, info_log);
      printf("error:shader:fragment - failed to compile\n%s\n", info_log);
    }}

    id = glCreateProgram();

    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    glLinkProgram(id);

    {int success;
    char info_log[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
      glGetProgramInfoLog(id, 512, nullptr, info_log);
      printf("error:shader:program - failed to link\n%s\n", info_log);
    }}

    glUseProgram(id);
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
  }

  void Shader::terminate() {
    glDeleteShader(this->id);
  }

  Shader &Shader::use() {
    glUseProgram(this->id);
    return *this;
  }
}
