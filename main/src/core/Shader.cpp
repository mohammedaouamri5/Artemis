
#include "Shader.hpp"
#include <cstdlib>
#include <fmt/base.h>
#include <fmt/core.h>
#include <iostream>
#include <string>


namespace CORE { 
// Access the shader source as const char*
Shader::Shader(const std::string &__str , GLuint shared) {
  this->shader = shared;

  if (source != NULL) {
    free(source);
  }
  source = (char *)malloc(__str.size() + 1);
  memcpy(source, __str.c_str(), __str.size());
  source[__str.size()] = '\0'; // Null-terminate
}




void Shader::checkShaderCompileStatus() {
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\nSource:\n" << getFormated() <<  std::endl;
  }
}

void Shader::checkProgramLinkingStatus() {
  GLint success;
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
    GLchar infoLog[512];
  if (!success) {
    glGetProgramInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
}

};
