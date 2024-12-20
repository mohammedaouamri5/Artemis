
#include <Loader/cube.hpp>
#include <cstdint>
#include <cstdlib>
#include <fmt/base.h>

// Cube::Cube() {
//
//   this->Vetexs = (float *)malloc(GetSizeVertices());
//   this->Color = (float *)malloc(GetSizeColor());
//   this->Element = (unsigned int *)malloc(GetSizeIndices());
//   for (int __x = -1, __index = 0; __x <= 1; __x += 2)
//     for (int __y = -1; __y <= 1; __y += 2)
//       for (int __z = -1; __z <= 1; __z += 2) {
//         this->Vetexs[__index++] = __x;
//         this->Vetexs[__index++] = __y;
//         this->Vetexs[__index++] = __z;
//         this->Vetexs[__index++] = 1.f;
//       }
//
//   for (int __index = 0; __index < GetSizeColor(); __index++) {
//     if (__index && not __index % 4 && GetDimColor() == 4)
//       this->Color[__index] = 1.f;
//     this->Color[__index] = float(__index) / GetSizeColor();
//   }
//
//   for (int i = 0, __index = 0; i < GetSizeIndices(); i += 4)
//     for (int ii = i + 4; ii < GetSizeColor(); ii += 4)
//       for (int iii = ii + 4; iii < GetSizeColor(); iii += 4) {
//         LOG_INFO("index {} : i = {}, ii = {}, iii = {}", __index, i, ii,
//         iii);
//         __index += 3;
//       }
// }
//
//

namespace Loader {
float *Cube::GetVertices() { return this->Vetexs; }
uint16_t Cube::GetNbVertices() { return 8; }
uint16_t Cube::GetDimVertices() { return 4; }
uint16_t Cube::GetSizeVertices() {
  return GetNbVertices() * sizeof(float) * GetDimVertices();
}

unsigned int *Cube::GetIndices() { return this->Element; }
uint16_t Cube::GetNbIndices() { return 12; }
uint16_t Cube::GetDimIndices() { return 3; }
uint16_t Cube::GetSizeIndices() {
  return GetNbIndices() * sizeof(unsigned int) * GetDimIndices();
}

float *Cube::GetColor() { return this->Color; }
uint16_t Cube::GetNbColor() { return 8; }
uint16_t Cube::GetDimColor() { return 4; }
uint16_t Cube::GetSizeColor() {
  return GetNbColor() * sizeof(float) * GetDimColor();
}

} // namespace Loader
