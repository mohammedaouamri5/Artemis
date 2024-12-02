
#include <glad/glad.h>
#include "Win.hpp"
#include "Layout.hpp"
#include "imgui.h"
#include "src/imgui/imgui_impl_glfw.h"
#include "src/imgui/imgui_impl_opengl3.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace CORE {

void CORE::Win::INIT() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    exit(5);
  }
  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(5);
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable V-Sync

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    exit(5);
  }
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplOpenGL3_Init("#version 460");
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  for (Layout *&layout : this->Layouts)
    layout->INIT();
}

int Win::INIT_LOOP() {
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  return 0;
}

void Win::RUN() {
  while (!glfwWindowShouldClose(Win::window)) {
    if (this->INIT_LOOP())
      continue;
    for (Layout *&layout : this->Layouts)
      layout->RUN();
    this->CLEAR_LOOP();
  }
}
void Win::CLEAR_LOOP() {
  ImGui::Render();
  glfwSwapBuffers(this->window);
  glfwPollEvents();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Win::CLOSE() {
  for (Layout *&layout : this->Layouts)
    layout->DIST();
  glfwTerminate();
}
} // namespace CORE
