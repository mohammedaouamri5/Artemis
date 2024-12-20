#include "core/Layout.hpp"
#include <glm/vec4.hpp>
#include "core/Shader.hpp"
#include <glad/glad.h>
#include <vector>

class Traingel : public CORE::Layout {
public:
  Traingel() {
    // Define the vertices of the triangle
  }
  void INIT() override;
  void RUN() override;
  void DIST() override;

  std::vector<float> vertices;
  std::vector<float> color; 
private:
  CORE::Shader *shaderProgram;
  unsigned int VAO, VBO,VBC, EBO; 
  

};

// Define the shader source code as static members of the class
