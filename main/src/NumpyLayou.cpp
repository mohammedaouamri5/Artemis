#include "Loader/Numpy.hpp"
#include "Loader/cube.hpp"
#include "imgui.h"
#include <NumpyLayou.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/format.h>
#include <string>
void NumpyLayout::ReAllocateNnmpy() {
  if (nullptr != this->numpy)
    delete numpy;
  this->numpy = new Loader::Numpy(this->path, __fov, threshold);
}
void NumpyLayout::ReAllocatePath() {
  if (path)
    free(path);
  if (this->path_size)
    this->path = (char *)malloc(this->path_size);
}
void NumpyLayout::INIT() {
  ReAllocatePath();
  __fov = 120.f;
}

static int counter = 0 ; 
void NumpyLayout::RUN() {
  ImGui::Begin("Numpy Layout");
  ImGui::InputInt("Path Size", &this->path_size);
  ImGui::InputText("Path", path, this->path_size);
  ImGui::InputFloat("FOV", &__fov);
  ImGui::InputFloat("Threshold", &threshold, 0.0, 0.0, "%.6f");
  if (ImGui::Button("Update Size"))
    ReAllocatePath();

  if (ImGui::Button("CONSTRTACT")) {
    ReAllocateNnmpy();
    ImGui::Text("START");
    numpy->Mesh();
    ImGui::Text("END");
    VAOLayout *WOW = new VAOLayout(std::to_string(rand()));
    LOG_INFO("VAO : {} \nprogram : {} \nIndeces : {}", WOW->VAO, WOW->program.getShader(), WOW->Indeces);
    numpy->INIT_THE_DROW(&WOW->VAO, &WOW->program, &WOW->Indeces);
    LOG_INFO("VAO : {} \nprogram : {} \nIndeces : {}", WOW->VAO, WOW->program.getShader(), WOW->Indeces);
    LOG_INFO("BRUH");
    VAOs.push_back(WOW);
    RUNss.push_back(false);
  }
  for (int __index = 0; __index < VAOs.size(); __index++) {
    if (ImGui::Button(fmt::format("RUN -> {} <-", __index).c_str())) {
      RUNss[__index] = !RUNss[__index];
    }
    if (RUNss[__index])
      VAOs[__index]->RUN();
  }

  ImGui::End();
}
void NumpyLayout::DIST() {}
