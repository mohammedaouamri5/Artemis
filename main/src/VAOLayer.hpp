

#include "core/Layout.hpp"
#include <Loader/cube.hpp>
#include <assimp/scene.h>
#include <core/Shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::perspective and glm::lookAt
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr (optional)
#include <string>

class VAOLayout : public CORE::Layout {
public:
  void RUN() override;
  ~VAOLayout() {}

public:
  unsigned int VAO;
  CORE::Shader program;
  uint64_t Indeces = 0;
  std::string name = "WOW"; 
  VAOLayout()  {}
  VAOLayout(std::string name):name(name)  {}

private:
  char *__path = nullptr;

  aiScene *scene = nullptr;

  glm::vec3 cameraPosition = glm::vec3(5.0f, 5.0f, 5.0f);
  glm::vec3 cameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), // Field of view
                                          800.0f / 600.0f,     // Aspect ratio
                                          0.001f,  // Near clipping plane
                                          100.0f // Far clipping plane
  );
  glm::mat4 model = glm::mat4(1.0f);

private:
};
