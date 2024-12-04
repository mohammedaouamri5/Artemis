#include "traingel.hpp"
#include "imgui.h"
#include "src/core/Shader.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/format.h>
#include <glm/vec4.hpp>
#include <iostream>

void Traingel::INIT() {
  // Generate and bind Vertex Array and Vertex Buffer objects

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Load the vertex data into the buffer
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  // Specify how OpenGL should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  vertexShader = new CORE::Shader("#version 460 core\n"
                                  "layout(location = {0}) in vec3 aPos;\n"
                                  "void main() {{\n"
                                  "    gl_Position = vec4(aPos, {1});\n"
                                  "}}\n",
                                  glCreateShader(GL_VERTEX_SHADER));
  fragmentShader = new CORE::Shader(R"(
              #version 460 core
              out vec4 FragColor;
              void main() {{
                  FragColor = vec4({},{},{},{}); // Orange color
              }})", 
                                    glCreateShader(GL_FRAGMENT_SHADER));
}

void Traingel::RUN() {
  int location = 0;
  float bruh = 1.f;

  vertexShader->GlShaderFormating(location, bruh);
  vertexShader->GlCompileShader();
  vertexShader->checkShaderCompileStatus();


  fragmentShader->GlShaderFormating(color.x, color.y, color.z, color.w);
  fragmentShader->GlCompileShader();
  fragmentShader->checkShaderCompileStatus();

  // Compile fragment shader

  this->shaderProgram->checkProgramLinkingStatus();
  // Link shaders to create a sjhader program
  this->shaderProgram = new CORE::Shader("", glCreateProgram());
  glAttachShader(this->shaderProgram->getShader(), vertexShader->getShader());
  glAttachShader(this->shaderProgram->getShader(), fragmentShader->getShader());
  glLinkProgram(this->shaderProgram->getShader());
  this->shaderProgram->checkProgramLinkingStatus();

  // Clean up shaders after they are linked

  glUseProgram(this->shaderProgram->getShader());
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDeleteShader(vertexShader->getShader());
  glDeleteShader(fragmentShader->getShader());
}

void Traingel::DIST() {
  glDeleteShader(vertexShader->getShader());
  glDeleteShader(fragmentShader->getShader());
  glDeleteProgram(shaderProgram->getShader());
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}
