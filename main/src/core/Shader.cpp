
#include "LOG.hpp"
#include "Shader.hpp"
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>
#include <fmt/core.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

namespace CORE {
// Access the shader source as const char*
Shader::Shader(const std::string &__str, GLuint shared) {
  
  this->shader = shared;

 if (__str.empty()) return ; 
 
  FILE *file = fopen(__str.c_str(), "r");
  if (file == NULL) {
    LOG_INFO("File not found {}", __str);
    LOG_CRITICAL("Failed to open shader file {}", __str);
  }

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (source != NULL) {
    free(source);
  }

  source = (char *)malloc(fileSize + 1);
  if (source == NULL) {
    LOG_CRITICAL("Failed to allocate memory for shader source");
  }

  fread(source, 1, fileSize, file);
  source[fileSize] = '\0';
  fclose(file);
  spdlog::info("Shader source: \n{}", source);
}

void Shader::checkShaderCompileStatus() {
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    LOG_ERROR("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog);
  }
}

void Shader::checkProgramLinkingStatus() {
  GLint success;
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  GLchar infoLog[512];
  if (!success) {
    glGetProgramInfoLog(shader, 512, NULL, infoLog);
    LOG_ERROR("ERROR::SHADER::LINKING_FAILED\n{}", infoLog);
  }
}

}; // namespace CORE
