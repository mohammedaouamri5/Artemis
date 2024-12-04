#ifndef SHADER_HPP
#define SHADER_HPP
#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <utility>

namespace CORE { 
class Shader {
private:
  char *source = nullptr;
  char *formated = nullptr;
  GLuint shader = 0;

public:
  // Constructor
  Shader(const std::string &format, GLuint shared);

  // Accessor methods
  inline const char *getSource() const { return source; }
  inline const char *getFormated() const { return formated; }
  inline GLuint getShader() const { return shader; }

  // Formatting and OpenGL operations
  template <typename... Args> char *format(Args &&...args);

  template <typename... Args> char *GlShaderFormating(Args &&...args);

  inline void GlCompileShader() { glCompileShader(shader); }
  inline void GlShaderSource(GLuint shader, GLsizei count,
                             const GLchar *const *string, const GLint *length) {
    glShaderSource(shader, count, string, length);
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

// Template method definitions

template <typename... Args> char *Shader::format(Args &&...args) {
  if (this->formated != nullptr) {
    free(this->formated);
    this->formated = nullptr;
  }


  std::string formatedStr =
      fmt::format(source, std::forward<Args>(args)...);
  this->formated = (char *)malloc(formatedStr.size() + 1);
  std::memcpy(this->formated, formatedStr.c_str(), formatedStr.size());
  this->formated[formatedStr.size()] = '\0'; // Null-terminate
  return this->formated;
}

template <typename... Args> char *Shader::GlShaderFormating(Args &&...args) {
  if (this->formated == nullptr) {
    format(std::forward<Args>(args)...);
  }

  glShaderSource(this->shader, 1, &this->formated, nullptr);
  return this->formated;
}

};
#endif // SHADER_HPP
