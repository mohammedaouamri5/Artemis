

#include "Layout.hpp"
#include <LOG.hpp>
#include <VAO.hpp>
#include <cstdlib>
#include <imgui.h>
#include <string>

VAO::VAO(glm::vec3 position, Loader::DATA *data) {
  Id = std::to_string(rand());

  indices_count = data->GetNbIndices();
  unsigned int VBO, CBO, EBO;
  // Generate and bind Vertex Array Object (VAO)
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Generate and bind Vertex Buffer Object (VBO) for vertex positions
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data->GetSizeVertices(), data->GetVertices(),
               GL_STATIC_DRAW);

  // Set vertex attribute pointer for positions (location = 0)
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Verify VBO size
  int VBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &VBO_size);
  if (VBO_size != data->GetSizeVertices()) {
    LOG_CRITICAL("VBO size mismatch");
  }

  // Generate and bind Color Buffer Object (CBO) for vertex colors
  glGenBuffers(1, &CBO);
  glBindBuffer(GL_ARRAY_BUFFER, CBO);
  glBufferData(GL_ARRAY_BUFFER, data->GetSizeColor(), data->GetColor(),
               GL_STATIC_DRAW);

  // Set vertex attribute pointer for colors (location = 1)
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // Verify CBO size
  int CBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &CBO_size);
  if (CBO_size != data->GetSizeColor()) {
    LOG_CRITICAL("CBO size mismatch");
  }

  // Generate and bind Element Buffer Object (EBO) for indices
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->GetSizeIndices(),
               data->GetIndices(), GL_STATIC_DRAW);

  // Unbind VAO (optional, good practice)
  glBindVertexArray(0);

  // Initialize shaders
  CORE::Shader vertexShader("assets/shaders/defult-vertex.glsl",
                            glCreateShader(GL_VERTEX_SHADER));
  CORE::Shader fragmentShader("assets/shaders/defult-fragment.glsl",
                              glCreateShader(GL_FRAGMENT_SHADER));

  // Load, compile, and check vertex shader
  vertexShader.GLshaderSource();
  vertexShader.GLcompileShader();
  vertexShader.checkShaderCompileStatus();

  // Load, compile, and check fragment shader
  fragmentShader.GLshaderSource();
  fragmentShader.GLcompileShader();
  fragmentShader.checkShaderCompileStatus();

  // Create and link shader program
  program = CORE::Shader("", glCreateProgram());
  glAttachShader(program.getShader(), vertexShader.getShader());
  glAttachShader(program.getShader(), fragmentShader.getShader());
  glLinkProgram(program.getShader());
  program.checkProgramLinkingStatus();

  // Clean up shader objects after linking
  glDeleteShader(vertexShader.getShader());
  glDeleteShader(fragmentShader.getShader());
}

void VAO::RUN() {
  glm::mat4 MVP = CORE::Layout::camera->projection_mat *
                  CORE::Layout::camera->view_mat *
                  glm::translate(glm::mat4(1.0f), position);

  // Use shader program and set MVP uniform
  glUseProgram(program.getShader());
  glUniformMatrix4fv(glGetUniformLocation(program.getShader(), "u_MVP"), 1,
                     GL_FALSE, &MVP[0][0]);

  glBindVertexArray(vao);

  // Start ImGui window
  ImGui::Begin(Id.c_str());

  // Add VAO information
  ImGui::Text("VAO Information:");
  ImGui::BulletText(" Indeces : %ld", indices_count);
  int maxAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);

  for (int i = 0; i < maxAttributes; i++) {
    GLint enabled = 0;
    glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
    if (enabled) {
      GLint buffer = 0, size = 0, stride = 0, type = 0;
      glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &buffer);
      glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
      glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
      glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);

      GLint64 bufferSize = 0;
      glBindBuffer(GL_ARRAY_BUFFER, buffer);
      glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

      int numVertices = 0;
      if (size > 0 && bufferSize > 0) {
        numVertices = bufferSize / (size * sizeof(float)); // Assuming GL_FLOAT
      }

      ImGui::Text("Attribute %d:", i);
      ImGui::BulletText("Buffer ID: %d", buffer);
      ImGui::BulletText("Size (dim): %d", size);
      ImGui::BulletText("Stride: %d", stride);
      ImGui::BulletText("Type: %s", type == GL_FLOAT ? "GL_FLOAT" : "Other");
      ImGui::BulletText("Buffer Size: %lld bytes", bufferSize);
      ImGui::BulletText("Number of Vertices: %d", numVertices);
    }
  }

  // End ImGui window
  ImGui::End();

  // Draw the object
  glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}
