#ifndef __VAO_HPP__
#define __VAO_HPP__
#include "Loader/data.hpp"
#include "Shader.hpp"
#include <glad/glad.h>

#include <Layout.hpp>
#include <glm/glm.hpp>
#include <string>

class VAO : public CORE::Layout {

  std::string Id;
  glm::vec3 position;
  unsigned int vao = 0;
  int indices_count;
  CORE::Shader program;
  bool Show = false;
  glm::vec4 transformation;
  float Roll;
  float Pitch;
  float Yaw;
  int rotation_first;

  glm::mat4 applyRotation();

public:
  VAO(glm::vec3 position, Loader::DATA *data);

  void RUN() override;
};

#endif
