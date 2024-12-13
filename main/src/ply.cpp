#include "ply.hpp"
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

PLY::PLY(const char *__path) {
  spdlog::info("Start Constractor");
  auto start_ = std::chrono::high_resolution_clock::now();
  this->__path = strdup(__path);
  Assimp::Importer importer;
  if (!importer.ReadFile(__path, 0)) {
    spdlog::critical("Failed to load PLY file {} , cuz {}", __path,
                     importer.GetErrorString());
    return;
  }
  this->scene = importer.GetOrphanedScene();
  if (!this->scene) {
    spdlog::critical("Failled to GetOrphanedScene ", __path);
    return;
  }
  auto end_ = std::chrono::high_resolution_clock::now();

  spdlog::info(
      "it took std::chrono::milliseconds == {}",
      std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_)
          .count());
  spdlog::info("End Constractor");
}

void PLY::INIT() {

  auto start_ = std::chrono::high_resolution_clock::now();
  const aiMesh *mesh = scene->mMeshes[0];
  const aiVector3D *__vertices = scene->mMeshes[0]->mVertices;
  const unsigned int length = scene->mMeshes[0]->mNumVertices;

  const unsigned int indiceSize = 3 * mesh->mNumFaces * sizeof(unsigned int);
  const unsigned int verticeSize = 4 * mesh->mNumVertices * sizeof(float);
  unsigned int *indices = (unsigned int *)malloc(indiceSize);
  float *vertices = (float *)malloc(verticeSize);

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    if (mesh->mFaces[i].mNumIndices != 3)
      spdlog::error("Face with more than 3 vertices");
    {
      indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
      indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
      indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
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
      "it took std::chrono::microseconds == {}",
      std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_)
          .count());

  // Generate VAO, VBO, and EBO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  int VBO_zise = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &VBO_zise);
  if (VBO_zise != verticeSize) {
    spdlog::critical("VBO size is 0");
    exit(1);
  }

  // Unbind VB
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Bind and load index data into EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, indices, GL_STATIC_DRAW);

  // Unbind VAO (optional but good practice)
  glBindVertexArray(0);

  // Initialize shaders
  vertexShader = new CORE::Shader("#version 330 core\n"
                                  "layout(location=0) in vec4 aPos;\n"
                                  "uniform mat4 u_MVP;\n"
                                  "void main() {{\n"
                                  "    gl_Position = u_MVP * aPos;\n"
                                  "}}\n",
                                  glCreateShader(GL_VERTEX_SHADER));

  fragmentShader = new CORE::Shader(R"(
                #version 330 core
                out vec4 FragColor;
                uniform vec4 u_Color;
                void main() {{
                    FragColor = vec4(u_Color); 
                }})",
                                    glCreateShader(GL_FRAGMENT_SHADER));
  vertexShader->GlShaderFormating();
  vertexShader->GlCompileShader();
  vertexShader->checkShaderCompileStatus();

  // Compile and check fragment shader
  fragmentShader->GlShaderFormating();
  fragmentShader->GlCompileShader();
  fragmentShader->checkShaderCompileStatus();

  // Create shader program and link shaders
  this->shaderProgram = new CORE::Shader("", glCreateProgram());
  glAttachShader(this->shaderProgram->getShader(), vertexShader->getShader());
  glAttachShader(this->shaderProgram->getShader(), fragmentShader->getShader());
  glLinkProgram(this->shaderProgram->getShader());
  this->shaderProgram->checkProgramLinkingStatus();

  // Clean up shaders after they are linked
  glDeleteShader(vertexShader->getShader());
  glDeleteShader(fragmentShader->getShader());
  spdlog::info("PLY INIT DONE");
}

void PLY::RUN() {
  auto start_ = std::chrono::high_resolution_clock::now();
  const aiMesh *mesh = scene->mMeshes[0];
  // Compile and check vertex shader

  glm::mat4 view = glm::lookAt(cameraPosition, cameraLookAt, Up);
  glm::mat4 MVP = this->projection * view * this->model;

  glUseProgram(this->shaderProgram->getShader());
  glUniform4f(glGetUniformLocation(this->shaderProgram->getShader(), "u_Color"),
              color.x, color.y, color.z, color.w);
  glUniformMatrix4fv(
      glGetUniformLocation(this->shaderProgram->getShader(), "u_MVP"), 1,
      GL_FALSE, &MVP[0][0]);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, mesh->mNumFaces * 3, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  auto end_ = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_)
          .count();
  ImGui::Begin("PLY");
  ImGui::DragFloat3("Camera Position", (float *)&cameraPosition[0], 0.1f);
  ImGui::DragFloat3("Look At", (float *)&cameraLookAt[0], 0.1f);
  ImGui::DragFloat3("Up", (float *)&Up[0], 0.1f);
  ImGui::DragFloat4("Color", (float *)&color[0], 0.1f);
  ImGui::Text("rending time: %ld", duration);
  ImGui::End();
}
