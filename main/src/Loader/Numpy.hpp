

#ifndef __NUMPY_HPP__
#define __NUMPY_HPP__

#include "data.hpp"
#include <LOG.hpp>
#include <Loader/data.hpp>
#include <cnpy.h>
#include <cstdint>
#include <vector>
namespace Loader {

class Numpy : public DATA {

  unsigned int C, H, W;
  cnpy::NpyArray m_data;

public:
  char *path = nullptr;
  std::vector<float> data;
  ~Numpy() {}
  Numpy() {}
  void Mesh();

  int Index(int i, int ii, int iii);
  Numpy(const char *__path); //  { LOG_INFO("WOW"); }

  // float *GetVertices() /* override */;
  // uint16_t GetNbVertices() /* override */;
  // uint16_t GetSizeVertices() /* override */;
  // uint16_t GetDimVertices() /* override */;
  // unsigned int *GetIndices() /* override */;
  // uint16_t GetNbIndices() /* override */;
  // uint16_t GetSizeIndices() /* override */;
  // uint16_t GetDimIndices() /* override */;
  // float *GetColor() /* override */;
  // uint16_t GetNbColor() /* override */;
  // uint16_t GetSizeColor() /* override */;
  // uint16_t GetDimColor() /* override */;
};

}; // namespace Loader

#endif // __NUMPY_HPP__
