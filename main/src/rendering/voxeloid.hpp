#pragma once

#include "glm/ext/vector_float4.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"
#include "core/Layout.hpp"
#include <assimp/Importer.hpp>

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

#include </home/omni/Desktop/me/Artemis/vendor/glad/glad.h>
#include <GLFW/glfw3.h>


class voxeloid : public CORE::Layout{
  private:
    glm::vec3 position;
    unsigned int vao;
    int indices_count;

  public:

  voxeloid(glm::vec3 pos , unsigned int Vao ,int indi_count):
  position(pos) , vao(Vao) , indices_count(indi_count){
    
  }

  void INIT() override{};
  void RUN() override {

   // Bind the VAO
    glBindVertexArray(vao);

    // Draw the geometry
    // If you are using indexed rendering:
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);

    // If you're not using indices (replace above call if needed):
    // glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    // Unbind the VAO (optional, for safety)
    glBindVertexArray(0);

    // Unbind the shader program (optional, for safety)

  };
    

};
