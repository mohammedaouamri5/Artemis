
#include <glad/glad.h>
#include "Win.hpp"
#include "Layout.hpp"
#include "src/imgui/imgui_impl_glfw.h"
#include "src/imgui/imgui_impl_opengl3.h"
#include <core/LOG.hpp>
#include <csetjmp>
#include <cstdlib>
#include <iostream>

#include <spdlog/spdlog.h>
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
  /* Initialize GLFW */ {
    if (!glfwInit()) {
      spdlog::error("Failed to initialize GLFW");
      exit(5);
    }
  }

  /* Create a windowed mode window and its OpenGL context */ {
    window = glfwCreateWindow(800, 800, "OpenGL with ImGui", NULL, NULL);
    if (!window) {
      LOG_ERROR("Failed to create GLFW window");
      glfwTerminate();
      exit(5);
    }
  }

  /* Make the window's context current */ {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync
  }

  /* Initialize GLAD*/ {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      LOG_ERROR("Failed to initialize GLAD");
      exit(5);
    }
  }

  /* Initialize ImGui context*/ {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
  }

  /* Initialize ImGui GLFW/OpenGL bindings */ {
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
  }

  // Initialize layouts
  for (Layout *&layout : this->Layouts)
    layout->INIT();
}

inline int Win::INIT_LOOP() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  glClear(GL_COLOR_BUFFER_BIT);
  return 0;
}

void CORE::Win::RUN() {
  while (!glfwWindowShouldClose(Win::window)) {
    if (this->INIT_LOOP())
      continue;

    for (Layout *&layout : this->Layouts)
      layout->RUN();
    this->CLEAR_LOOP();
  }
}
inline void Win::CLEAR_LOOP() {
  ImGui::Render();
  glClear(0);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
  glfwSwapBuffers(this->window);
  glfwPollEvents();
}

void Win::CLOSE() {
  for (Layout *&layout : this->Layouts)
    layout->DIST();
  glfwTerminate();
}
} // namespace CORE
