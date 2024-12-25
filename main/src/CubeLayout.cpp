#include "CubeLayout.hpp"
#include "glm/ext/vector_float4.hpp"
#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"
#include "src/core/Shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::perspective and glm::lookAt
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr (optional)
#include <imgui.h>

CubeLayout::CubeLayout(const char *__path) {
  spdlog::info("Start Constractor");

  this->cube = new Loader::Cube();
  spdlog::info("End Constractor");
}

void CubeLayout::INIT() {
  // Generate and bind Vertex Array Object (VAO)
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Generate and bind Vertex Buffer Object (VBO) for vertex positions
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, cube->GetSizeVertices(), cube->GetVertices(),
               GL_STATIC_DRAW);

  // Set vertex attribute pointer for positions (location = 0)
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Verify VBO size
  int VBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &VBO_size);
  if (VBO_size != cube->GetSizeVertices()) {
    LOG_CRITICAL("VBO size mismatch");
  }

  // Generate and bind Color Buffer Object (CBO) for vertex colors
  glGenBuffers(1, &CBO);
  glBindBuffer(GL_ARRAY_BUFFER, CBO);
  glBufferData(GL_ARRAY_BUFFER, cube->GetSizeColor(), cube->GetColor(),
               GL_STATIC_DRAW);

  // Set vertex attribute pointer for colors (location = 1)
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // Verify CBO size
  int CBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &CBO_size);
  if (CBO_size != cube->GetSizeColor()) {
    LOG_CRITICAL("CBO size mismatch");
  }
  LOG_INFO("GetNbIndices: {}", cube->GetNbIndices());
  for (int __index = 0; __index < cube->GetNbIndices(); __index++) {
    LOG_INFO("Index: {}", cube->GetIndices()[__index]);
  }

  // Generate and bind Element Buffer Object (EBO) for indices
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->GetSizeIndices(),
               cube->GetIndices(), GL_STATIC_DRAW);

  // Unbind VAO (optional, good practice)
  glBindVertexArray(0);

  // Initialize shaders
  vertexShader = new CORE::Shader("assist/shaders/cube_vertex.glsl",
                                  glCreateShader(GL_VERTEX_SHADER));
  fragmentShader = new CORE::Shader("assist/shaders/cube_fragment.glsl",
                                    glCreateShader(GL_FRAGMENT_SHADER));

  // Load, compile, and check vertex shader
  vertexShader->GLshaderSource();
  vertexShader->GLcompileShader();
  vertexShader->checkShaderCompileStatus();

  // Load, compile, and check fragment shader
  fragmentShader->GLshaderSource();
  fragmentShader->GLcompileShader();
  fragmentShader->checkShaderCompileStatus();

  // Create and link shader program
  shaderProgram = new CORE::Shader("", glCreateProgram());
  glAttachShader(shaderProgram->getShader(), vertexShader->getShader());
  glAttachShader(shaderProgram->getShader(), fragmentShader->getShader());
  glLinkProgram(shaderProgram->getShader());
  shaderProgram->checkProgramLinkingStatus();

  // Clean up shader objects after linking
  glDeleteShader(vertexShader->getShader());
  glDeleteShader(fragmentShader->getShader());

  spdlog::info("Cube initialization completed.");
}

void CubeLayout::RUN() {
  auto start = std::chrono::high_resolution_clock::now();

  // Calculate view and MVP matrices
  glm::mat4 view = glm::lookAt(cameraPosition, cameraLookAt, Up);
  glm::mat4 MVP = projection * view * model;

  // Use shader program and set MVP uniform
  glUseProgram(shaderProgram->getShader());
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getShader(), "u_MVP"),
                     1, GL_FALSE, &MVP[0][0]);

  // Bind VAO and render elements
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES,3, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);







  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  // ImGui interface for real-time adjustments
  ImGui::Begin("Cube Properties");
  ImGui::DragFloat3("Camera Position", &cameraPosition[0], 0.1f);
  ImGui::DragFloat3("Look At", &cameraLookAt[0], 0.1f);
  ImGui::DragFloat3("Up", &Up[0], 0.1f);
  ImGui::DragFloat4("Color", &color[0], 0.01f, 0.0f, 1.0f);
  ImGui::Text("Rendering Time: %ld microseconds", duration);
  ImGui::End();
}
