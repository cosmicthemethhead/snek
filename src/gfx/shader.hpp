#pragma once

namespace gfx {
  struct Shader {
    unsigned int id;
    Shader() { };

    void compile(const char* vertex_src, const char* fragment_src);
    void terminate();

    Shader &use();
  };
}
