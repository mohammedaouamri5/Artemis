//
//
#ifndef __CUBE_HPP__
#define __CUBE_HPP__
// #include <Loader/data.hpp>
#include "Loader/data.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/geometric.hpp"
#include <core/LOG.hpp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <sys/types.h>

namespace Loader {

class Cube : public DATA {
public:
  float *Vetexs;
  unsigned int *Element;
  float *Color;
  ~Cube() = default;

  Cube() {

    this->Vetexs = (float *)malloc(GetSizeVertices());
    this->Color = (float *)malloc(GetSizeColor());
    this->Element = (unsigned int *)malloc(GetSizeIndices());

    float tempVertices[] = {
        -1.f, -1.f, -1.f, 1.f, // vertex 0
        -1.f, -1.f, 1.f,  1.f, // vertex 1
        -1.f, 1.f,  -1.f, 1.f, // vertex 2
        -1.f, 1.f,  1.f,  1.f, // vertex 3
        1.f,  -1.f, -1.f, 1.f, // vertex 4
        1.f,  -1.f, 1.f,  1.f, // vertex 5
        1.f,  1.f,  -1.f, 1.f, // vertex 6
        1.f,  1.f,  1.f,  1.f  // vertex 7
    };
    std::memcpy(this->Vetexs, tempVertices, GetSizeVertices());

    unsigned int tempIndices[] = {
        0, 1, 4, // face 0
        5, 1, 4, // face 1
        0, 4, 6, // face 2
        0, 2, 6, // face 3
        0, 2, 1, // face 4
        3, 2, 1, // face 5
        3, 2, 6, // face 6
        3, 7, 6, // face 7
        3, 7, 1, // face 8
        5, 7, 1, // face 9
        5, 4, 7, // face 10
        5, 4, 6, // face 11
    };

    LOG_INFO("Cube indices size: {}", GetSizeIndices());
    LOG_INFO("tmp size: {}", sizeof(tempIndices));
    std::memcpy(this->Element, tempIndices, GetSizeIndices());

    for (int __index = 0; __index < GetNbColor() * GetDimColor(); __index++) {
      if (__index && not __index % 4 && GetDimColor() == 4)
        this->Color[__index] = 1.f;
      this->Color[__index] = float((rand() % 255) + 100) / 255.f;
    }
  }

  float *GetVertices() /* override */;
  uint64_t GetNbVertices() /* override */;
  uint64_t GetSizeVertices() /* override */;
  uint64_t GetDimVertices() /* override */;
  unsigned int *GetIndices() /* override */;
  uint64_t GetNbIndices() /* override */;
  uint64_t GetSizeIndices() /* override */;
  uint64_t GetDimIndices() /* override */;
  float *GetColor() /* override */;
  uint64_t GetNbColor() /* override */;
  uint64_t GetSizeColor() /* override */;
  uint64_t GetDimColor() /* override */;
};
} // namespace Loader

#endif
