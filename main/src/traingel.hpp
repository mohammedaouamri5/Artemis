#include "core/Layout.hpp"
#include <glad/glad.h>
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
  GLuint VAO, VBO, shaderProgram;
  std::vector<float> vertices; // The vertex data for the triangle

  // Check shader compilation status
  void checkShaderCompileStatus(GLuint shader);
  // Check program linking status
  void checkProgramLinkingStatus(GLuint program);


  // Vertex Shader source code
  static const char *vertexShaderSource;
  // Fragment Shader source code
  static const char *fragmentShaderSource;
};

// Define the shader source code as static members of the class
