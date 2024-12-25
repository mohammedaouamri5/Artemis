#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

#include "genralobject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext/vector_float4.hpp"
#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>



class plyobject : protected object{
  private:

  char* filepath = NULL;
  aiScene *scene = NULL;
  unsigned int vbo,ebo;

void load_content(){
    spdlog::info("started loading file contents");
  auto start_ = std::chrono::high_resolution_clock::now();
  this->filepath = strdup(filepath);
  Assimp::Importer importer;

  if (!importer.ReadFile(filepath, 0)) {
    spdlog::critical("Failed to load PLY file {} , cuz {}", filepath,
                     importer.GetErrorString());
    return;
  }

  this->scene = importer.GetOrphanedScene();
  if (!this->scene) {
    spdlog::critical("Failled to GetOrphanedScene ", filepath);
    return;
  }

  auto end_ = std::chrono::high_resolution_clock::now();

  spdlog::info(
      "it took : (miliseconds)",
      std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_)
          .count());
  spdlog::info("loading completed .\n");


}

void initialize_buffers(){
  
  auto start_ = std::chrono::high_resolution_clock::now();
  const aiMesh *mesh = scene->mMeshes[0];
  const aiVector3D *__vertices = scene->mMeshes[0]->mVertices;
  const unsigned int length = scene->mMeshes[0]->mNumVertices;

  const unsigned int indiceSize = 3 * mesh->mNumFaces * sizeof(unsigned int);
  const unsigned int verticeSize = 4 * mesh->mNumVertices * sizeof(float);
  
  faces = (unsigned int *)malloc(indiceSize);
  vertices = (float *)malloc(verticeSize);

  vertices_count = mesh->mNumVertices;
  faces_count = mesh->mNumFaces;


  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    if (mesh->mFaces[i].mNumIndices != 3)
      spdlog::error("Face with more than 3 vertices");
    {
      faces[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
      faces[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
      faces[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
    }
  }

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    glm::vec4 vec(__vertices[i].x, __vertices[i].y, __vertices[i].z, 1.f);

    {
      vertices[i * 4 + 0] = vec.x;
      vertices[i * 4 + 1] = vec.y;
      vertices[i * 4 + 2] = vec.z;
      vertices[i * 4 + 3] = vec.w;
    }
  }

  auto end_ = std::chrono::high_resolution_clock::now();

  spdlog::info(
      "time to prepare data:",
      std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_)
          .count());

// Generate VAO, VBO, and EBO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  int VBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &VBO_size);
  if (VBO_size != verticeSize) {
    spdlog::critical("VBO size is 0");
    exit(1);
  }

  // Unbind vbo
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Bind and load index data into EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, faces, GL_STATIC_DRAW);

  int EBO_size = 0;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &EBO_size);
  if (EBO_size != indiceSize) {
    spdlog::critical("EBO size mismatch!");
    exit(1);
}

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  // Unbind VAO (optional but good practice)
  glBindVertexArray(0);

  if (!vao || !vbo || !ebo) {
      spdlog::critical("Failed to generate VAO/VBO/EBO");
      exit(1);
  }

  printf("VAO ID: %d\n", vao);
  printf("VBO ID: %d\n", vbo);
  printf("EBO ID: %d\n", ebo);


}

  inline aiScene *getScene() { return scene; }

  public:

  int vertices_count=0;
  int faces_count=0;

  inline plyobject(char *path) : filepath(path){load_content();initialize_buffers();}

  unsigned int get_vao(){
    return vao;
  }

};

