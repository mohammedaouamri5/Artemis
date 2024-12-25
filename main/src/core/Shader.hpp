#ifndef SHADER_HPP
#define SHADER_HPP
#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <glad/glad.h>
#include <string>
#include <utility>

namespace CORE {
class Shader {
private:
  char *source = nullptr;
  char *formated = nullptr;
  unsigned int shader = 0;

public:
  Shader();
  // Constructor
  Shader(const std::string &format, GLuint shared);

  // Accessor methods
  inline const char *getSource() const { return source; }
  inline const char *getFormated() const { return formated; }
  inline GLuint getShader() const { return shader; }

  // Formatting and OpenGL operations
  template <typename... Args> char *format(Args &&...args);

  template <typename... Args> char *GlShaderFormating(Args &&...args);

  inline void GLcompileShader() { glCompileShader(shader); }
  inline void GLshaderSource(GLuint shader, GLsizei count,
                             const GLchar *const *string, const GLint *length) {
    glShaderSource(shader, count, string, length);
  }
  inline void GLshaderSource() {
    glShaderSource(this->shader, 1, &this->source, nullptr);
  }
  void checkShaderCompileStatus();
  void checkProgramLinkingStatus();

  // Delete copy constructor and copy assignment for uniqueness
  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  // Enable move constructor and assignment
  Shader(Shader &&) noexcept = default;
  Shader &operator=(Shader &&) noexcept = default;

  // Destructor
  ~Shader() {
    if (source != nullptr) {
      free(source);
    }
    if (formated != nullptr) {
      free(formated);
    }
  }
};

template <typename... Args> char *Shader::GlShaderFormating(Args &&...args) {
  glShaderSource(this->shader, 1, &this->formated, nullptr);
  return this->source;
}

}; // namespace CORE
#endif // SHADER_HPP
