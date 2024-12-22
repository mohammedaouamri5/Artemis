#include "imgui.h"
#include <NumpyLayou.hpp>
#include <cstdlib>
#include <cstring>
void NumpyLayout::ReAllocateNnmpy() {
  if (nullptr != this->numpy)
    delete numpy;
  this->numpy = new Loader::Numpy(this->path);
}
void NumpyLayout::ReAllocatePath() {
  if (path)
    free(path);
  if (this->path_size)
    this->path = (char *)malloc(this->path_size);
}
void NumpyLayout::INIT() {
  ReAllocatePath();
  // memcpy(this->path, "matrix.npy", 11);
}
void NumpyLayout::RUN() {
  ImGui::Begin("Numpy Layout");
  ImGui::InputText("Path", path, this->path_size);
  ImGui::InputInt("Path Size", &this->path_size);
  if (ImGui::Button("Update Size"))
    ReAllocatePath();

  if (ImGui::Button("Load"))
    ReAllocateNnmpy();

  if (ImGui::Button("CONSTRTACT")) {
    ImGui::Text("START");
    numpy->Mesh();
    ImGui::Text("END");
  }

  ImGui::End();
}
void NumpyLayout::DIST() {}
