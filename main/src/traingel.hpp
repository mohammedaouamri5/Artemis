#include "core/Layout.hpp"
#include "glm/vec4.hpp"
#include "src/core/Shader.hpp"
#include <glad/glad.h>
#include <iostream>
#include <vector>

class Traingel : public CORE::Layout {
public:
  Traingel() {
    // Define the vertices of the triangle
    vertices = {-0.5f, -0.5f, 0.0f,  // Bottom left
                0.5f,  -0.5f, 0.0f,  // Bottom right
                0.0f,  0.5f,  0.0f}; // Top center
  }
  void INIT() override;
  void RUN() override;
  void DIST() override;

private:
  GLuint VAO, VBO;
  CORE::Shader *shaderProgram;
  CORE::Shader *vertexShader = NULL, *fragmentShader = NULL;
  std::vector<float> vertices; // The vertex data for the triangle

private: // ImGui 

  glm::vec4 color = {1.0f, 0.5f, 0.2f, 1.0f};
  float bruh = 1.0f;


};

// Define the shader source code as static members of the class
