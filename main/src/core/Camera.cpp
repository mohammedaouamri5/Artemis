#include <Camera.hpp>
#include <LOG.hpp>
#include <cmath>
#include <imgui.h>
#include <zconf.h>

namespace CORE {

void Camera::updateProjection() {

  projection_mat =
      glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
}

Camera::Camera(glm::vec4 startpos, GLFWwindow *win, int h, int w)
    : position(startpos), window(win), height(h), width(w), up(0, 1, 0),
      forward(0, 1, 0), right(0, 1, 0), fov(45.0f), near_plane(0.1),
      far_plane(1000.0f), aspect_ratio(float(width) / height), mouse_x(0),
      mouse_y(0) {
  updateProjection();
}

inline void Camera::updateCameraVectors() {
  forward.x = cos(yaw) * cos(pitch);
  forward.y = sin(pitch);
  forward.z = sin(yaw) * cos(pitch);
  forward = glm::normalize(forward);
  right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
  view_mat = glm::lookAt(position, position + forward, up);
}

inline void Camera::debugCamera() const {
  ImGui::Begin("CAMERA");

  // Header with a standout color
  ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f),
                     "Camera Debug Information");

  // Position section
  ImGui::Separator();
  ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.4f, 1.0f), "Position:");
  ImGui::Text("X: %.2f Y: %.2f Z: %.2f", position.x, position.y, position.z);

  // Forward section
  ImGui::Separator();
  ImGui::TextColored(ImVec4(0.4f, 0.8f, 0.4f, 1.0f), "Forward:");
  ImGui::Text("X: %.2f Y: %.2f Z: %.2f", forward.x, forward.y, forward.z);

  // Right section
  ImGui::Separator();
  ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.4f, 1.0f), "Right:");
  ImGui::Text("X: %.2f Y: %.2f Z: %.2f", right.x, right.y, right.z);

  // Up section
  ImGui::Separator();
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.8f, 1.0f), "Up:");
  ImGui::Text("X: %.2f Y: %.2f Z: %.2f", up.x, up.y, up.z);

  ImGui::End();
}

inline void Camera::moveCamera() {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    position += 0.5f * forward;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    position -= 0.5f * forward;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    position -= 0.5f * right;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    position += 0.5f * right;
  }
}

inline void Camera::updateRotation() {
  glfwGetCursorPos(window, &mouse_x, &mouse_y);

  yaw += asin((mouse_x / width - 0.5) );
  pitch += asin((mouse_y / height - 0.5) );
  double centerX = width / 2.0;
  double centerY = height / 2.0;
  glfwSetCursorPos(window, centerX, centerY);
}

void Camera::INIT() {
  // Initialization logic if needed
}

inline void Camera::ImGuiEditor() {

  ImGui::Begin("CAMERA");

  // Add sliders for yaw and pitch

  ImGui::Text("Camera Position");
  ImGui::SliderFloat("Yaw", &this->yaw, -glm::pi<float>(), glm::pi<float>());
  ImGui::SliderFloat("Pitch", &pitch, -glm::half_pi<float>(),
                     glm::half_pi<float>());


  // Add buttons aligned to represent directions
  ImGui::Text("Move Camera");

  // Center row
  ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 40); // Adjust to center
  if (ImGui::Button("↑ ")) {
    position += 0.5f * forward;
  }

  // Row with left, backward, and right buttons
  if (ImGui::Button("← ")) {
    position -= 0.5f * right;
  }
  ImGui::SameLine();
  if (ImGui::Button("↓ ")) {
    position -= 0.5f * forward;
  }
  ImGui::SameLine();
  if (ImGui::Button("→ ")) {
    position += 0.5f * right;
  }
  ImGui::NewLine(); 
  ImGui::Separator(); 
  ImGui::BulletText("Projection");
  ImGui::SliderFloat("FOV ", &fov,45.f, 180.f);

  ImGui::SliderFloat("NERA", &near_plane, 0.f, far_plane, "%.6f");
  ImGui::SliderFloat("FAR ", &far_plane , near_plane, 1e6f);
  updateProjection();

  





  ImGui::End();
}

void Camera::RUN() {

  if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    LOG_INFO("I");
    if (mode == MODE::MANUAL)
      mode = MODE::IMGUI;
  }
  if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
    LOG_INFO("O");
    if (mode == MODE::IMGUI)
      mode = MODE::MANUAL;
  }

  if (mode == MANUAL) {

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    updateRotation();
    moveCamera();
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    ImGuiEditor();
  }
  updateCameraVectors();

  // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_mat));
  // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
  //                  glm::value_ptr(projection_mat));

  debugCamera();
}
} // namespace CORE
