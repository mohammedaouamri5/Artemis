
#include <Loders/cube.hpp>
#include <cstdint>
#include <cstdlib>

uint16_t Cube::GetNbVertices() { return 8; }
uint16_t Cube::GetDimVertices() { return 4; }
uint16_t Cube::GetSizeVertices() {
  return GetNbVertices() * sizeof(float) * GetDimVertices();
}

uint16_t Cube::GetNbIndices() { return 6; }
uint16_t Cube::GetDimIndices() { return 1; }
uint16_t Cube::GetSizeIndices() {
  return GetNbIndices() * sizeof(unsigned int) * GetDimIndices();
}

uint16_t Cube::GetNbColor() { return 8; }
uint16_t Cube::GetDimColor() { return 4; }
uint16_t Cube::GetSizeColor() {
  return GetNbColor() * sizeof(float) * GetDimColor();
}

