
#include "Shader.hpp"
#include <cstdlib>
#include <fmt/core.h>
#include <string>

// Access the shader source as const char*
inline const char *Shader::getSource() const { return source; }
Shader::Shader(const std::string &__str) {

  if (source != NULL) {
    free(source);
  }
  source = (char *)malloc(__str.size() + 1);
  memcpy(source, __str.c_str(), __str.size());
  source[__str.size()] = '\0'; // Null-terminate
}
template <typename... Args> std::string Shader::format(Args &&...args) {
  return fmt::format(this->source, std::forward<Args>(args)...);
}

void Shader::GlShaderSource(GLuint shader, GLsizei count, const GLchar *const *string,
                    const GLint *length){
    glShaderSource(shader, count, string, length);

}
void Shader::GlCompileShader(GLuint shader){
    glCompileShader(shader);
}
