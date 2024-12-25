#pragma once
#include <glad/glad.h>

#include "glm/ext/vector_float4.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"
#include "/home/omni/Desktop/me/Artemis/main/src/core/Layout.hpp"
#include <assimp/Importer.hpp>

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

#include <GLFW/glfw3.h>
#


class voxeloid : public CORE::Layout{
  private:
    glm::vec3 position;
    unsigned int vao;
    int indices_count;
    unsigned int shader;

  public:

  voxeloid(glm::vec3 pos , unsigned int vertex_att_obj ,int indi_count , unsigned int Shader):
  position(pos) , vao(vertex_att_obj) , indices_count(indi_count) , shader(Shader){
    
  }

  void INIT() override{};
  void RUN() override {

   // Bind the VAO
    glUseProgram(shader);
    
    glBindVertexArray(vao);

    // Draw the geometry
    // If you are using indexed rendering:
    glDrawArrays(GL_TRIANGLES ,0, indices_count*3);

    // If you're not using indices (replace above call if needed):
    // glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    // Unbind the VAO (optional, for safety)
    glBindVertexArray(0);

    // Unbind the shader program (optional, for safety)

  };
    

};
