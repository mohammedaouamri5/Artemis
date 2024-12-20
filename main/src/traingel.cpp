#include "traingel.hpp"
#include "imgui.h"
#include "src/core/Shader.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/format.h>
#include <glm/vec4.hpp>
#include <spdlog/spdlog.h>

void Traingel::INIT() {
// Generate and bind Vertex Array and Vertex Buffer objects
#define number_indices 3
  // Define vertices and indices
  vertices = {
      -0.5f, -0.5f, 0.0f, // Vertex 0
      0.5f,  -0.5f, 0.0f, // Vertex 1
      -0.5f, 0.5f,  0.0f, // Vertex 2
  };
  color = {

      1.f, 0.f, .0f, // Vertex 0
      0.f, 1.f, .0f, // Vertex 1
      0.f, 0.f, 1.f, // Vertex 2
  };

  unsigned int indices[] = {0, 1, 2};

  // Generate VAO, VBO, and EBO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &VBC);
  glGenBuffers(1, &EBO);

  // Bind VAO
  glBindVertexArray(VAO);

  // Bind and load vertex data into VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBC);
  glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(float), color.data(),
               GL_STATIC_DRAW);

  // Specify vertex attribute for position (location = 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // Bind and load vertex data into VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  // Specify vertex attribute for position (location = 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Bind and load index data into EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Unbind VAO (optional but good practice)
  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  // Initialize shaders
  CORE::Shader *vertexShader = new CORE::Shader(
      "shaders/traingel_vertex.glsl", glCreateShader(GL_VERTEX_SHADER));

  CORE::Shader *geometryShader = new CORE::Shader(
      "shaders/traingel_geometry.glsl", glCreateShader(GL_GEOMETRY_SHADER));

  CORE::Shader *fragmentShader = new CORE::Shader(
      "shaders/traingel_fragment.glsl", glCreateShader(GL_FRAGMENT_SHADER));

  {
    {
      vertexShader->GLshaderSource();
      vertexShader->GLcompileShader();
      vertexShader->checkShaderCompileStatus();
    }
    {
      geometryShader->GLshaderSource();
      geometryShader->GLcompileShader();
      geometryShader->checkShaderCompileStatus();
    }
    {
      fragmentShader->GLshaderSource();
      fragmentShader->GLcompileShader();
      fragmentShader->checkShaderCompileStatus();
    }
  }

  this->shaderProgram = new CORE::Shader("", glCreateProgram());

  /* NOTE : linking shaders */ {
    glAttachShader(this->shaderProgram->getShader(), vertexShader->getShader());
    glAttachShader(this->shaderProgram->getShader(),
                   geometryShader->getShader());
    glAttachShader(this->shaderProgram->getShader(),
                   fragmentShader->getShader());
    glLinkProgram(this->shaderProgram->getShader());
    this->shaderProgram->checkProgramLinkingStatus();
  }

  /* NOTE : clean up */ {
    glDeleteShader(vertexShader->getShader());
    glDeleteShader(geometryShader->getShader());
    glDeleteShader(fragmentShader->getShader());
  }
}

void Traingel::RUN() {
  if (1) {
    ImGui::ShowDemoWindow();
    glUseProgram(this->shaderProgram->getShader());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, number_indices, GL_UNSIGNED_INT,
                   nullptr); // Correct number of indices
    glUseProgram(0);
  } else {

    GLint vertices[] = {
        0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, -1, 1, 0, -1, 0, 0,
    };

    GLubyte colors[] = {
        255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 0, 255, 0, 255, 255,
    };

    GLubyte indices[] = {
        0, 1, 2, 3, 0, 3, 4, 5,
    };

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
    glVertexPointer(3, GL_INT, 0, vertices);
    glDrawElements(GL_QUADS, sizeof(indices) / sizeof(GLubyte),
                   GL_UNSIGNED_BYTE, indices);
  }
}

void Traingel::DIST() {
  // Clean up resources
  glDeleteProgram(shaderProgram->getShader());
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}
