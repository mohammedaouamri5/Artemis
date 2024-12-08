#include "traingel.hpp"
#include "src/core/Shader.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/format.h>
#include <glm/vec4.hpp>
#include <spdlog/spdlog.h>

void Traingel::INIT() {
// Generate and bind Vertex Array and Vertex Buffer objects
#define number_indices 6
  // Define vertices and indices
  vertices = {
      -0.5f, -0.5f, 0.0f, // Vertex 0
      0.5f,  -0.5f, 0.0f, // Vertex 1
      -1.f,  1.f,   0.0f, // Vertex 2
      0.0f,  0.0f,  0.0f  // Vertex 2
  };
  unsigned int indices[] = {3, 1, 0, 0, 2, 3};

  // Generate VAO, VBO, and EBO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind VAO
  glBindVertexArray(VAO);

  // Bind and load vertex data into VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  // Specify vertex attribute for position (location = 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Bind and load index data into EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Unbind VAO (optional but good practice)
  glBindVertexArray(0);

  // Initialize shaders
  vertexShader = new CORE::Shader("#version 460 core\n"
                                  "layout(location=0) in vec4 aPos;\n"
                                  "void main() {{\n"
                                  "    gl_Position = aPos;\n"
                                  "}}\n",
                                  glCreateShader(GL_VERTEX_SHADER));

  fragmentShader = new CORE::Shader(R"(
                #version 460 core
                out vec4 FragColor;
                void main() {{
                    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Orange color
                }})",
                                    glCreateShader(GL_FRAGMENT_SHADER));
}

void Traingel::RUN() {
  // Compile and check vertex shader
  vertexShader->GlShaderFormating();
  vertexShader->GlCompileShader();
  vertexShader->checkShaderCompileStatus();

  // Compile and check fragment shader
  fragmentShader->GlShaderFormating();
  fragmentShader->GlCompileShader();
  fragmentShader->checkShaderCompileStatus();

  // Create shader program and link shaders
  this->shaderProgram = new CORE::Shader("", glCreateProgram());
  glAttachShader(this->shaderProgram->getShader(), vertexShader->getShader());
  glAttachShader(this->shaderProgram->getShader(), fragmentShader->getShader());
  glLinkProgram(this->shaderProgram->getShader());
  this->shaderProgram->checkProgramLinkingStatus();

  // Clean up shaders after they are linked
  glDeleteShader(vertexShader->getShader());
  glDeleteShader(fragmentShader->getShader());

  // Use the shader program
  glUseProgram(this->shaderProgram->getShader());

  // Bind VAO and draw
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
                 nullptr); // Correct number of indices
}

void Traingel::DIST() {
  // Clean up resources
  glDeleteProgram(shaderProgram->getShader());
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}
