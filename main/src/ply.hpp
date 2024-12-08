
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::perspective and glm::lookAt
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr (optional)

#include "core/Layout.hpp"
#include "src/core/Shader.hpp"
#include <assimp/scene.h>
#include <glm/glm.hpp>
class PLY : public CORE::Layout {
public:
  inline aiScene *getScene() { return scene; }
  void INIT() override;
  void RUN() override;
  PLY(const char *__path);
  ~PLY();

public:
private:
  char *__path = nullptr;
  aiScene *scene = nullptr;
  GLuint VAO, VBO, EBO;
  CORE::Shader *shaderProgram;
  CORE::Shader *vertexShader = NULL, *fragmentShader = NULL;
  glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
  glm::vec3 cameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), // Field of view
                                          800.0f / 600.0f,     // Aspect ratio
                                          0.1f,  // Near clipping plane
                                          100.0f // Far clipping plane
  );
  glm::mat4 model = glm::mat4(1.0f);

private:
};
