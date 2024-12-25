#include "Loader/Numpy.hpp"
#include <VAOLayer.hpp>
#include <cstdlib>
#include <fmt/format.h>
#include <imgui.h>

void VAOLayout::RUN() {
  glm::mat4 view = glm::lookAt(cameraPosition, cameraLookAt, Up);
  glm::mat4 MVP = projection * view * model;

  // Use shader program and set MVP uniform
  glUseProgram(program.getShader());
  glUniformMatrix4fv(glGetUniformLocation(program.getShader(), "u_MVP"), 1,
                     GL_FALSE, &MVP[0][0]);

  glBindVertexArray(VAO);

  // Start ImGui window
  ImGui::Begin(name.c_str());

  // Camera Controls
  ImGui::DragFloat3("Camera Position", &cameraPosition[0], 0.1f);
  ImGui::DragFloat3("Look At", &cameraLookAt[0], 0.1f);
  ImGui::DragFloat3("Up", &Up[0], 0.1f);

  // Add VAO information
  ImGui::Text("VAO Information:");
      ImGui::BulletText(" Indeces : %ld", Indeces);
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
  glDrawElements(GL_TRIANGLES, Indeces, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}
