

#ifndef __NUMPY_HPP__
#define __NUMPY_HPP__

#include "Shader.hpp"
#include "data.hpp"
#include "glm/ext/vector_float4.hpp"
#include "imgui.h"
#include <LOG.hpp>
#include <Loader/data.hpp>
#include <cnpy.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
namespace Loader {

class Numpy : public DATA {

  glm::vec4 Point(int x, int y, float z);

  unsigned int C, H, W;
  cnpy::NpyArray m_data;
  float fov, tan_rad_fov, threshold;

  std::vector<float> Vertex;
  std::vector<unsigned int> Indices;
  std::vector<float> Color;

public:
  char *path = nullptr;
  std::vector<float> data;
  ~Numpy() {}
  Numpy() {}
  void Mesh();

  void AddFace(unsigned int First, unsigned int Second, unsigned int Third);
  int Index(int i, int ii, int iii);

  Numpy(const char *__path, float __fov,
        float __threshold); //  { LOG_INFO("WOW"); }

  void INIT_THE_DROW(unsigned int *VAO, CORE::Shader *program,
                     uint64_t  *NbIndices) /* override */;

  float *GetVertices() override;
  uint64_t GetNbVertices() override;
  uint64_t GetSizeVertices() override;
  uint64_t GetDimVertices() override;
  unsigned int *GetIndices() override;
  uint64_t GetNbIndices() override;
  uint64_t GetSizeIndices() override;
  uint64_t GetDimIndices() override;
  float *GetColor() override;
  uint64_t GetNbColor() override;
  uint64_t GetSizeColor() override;
  uint64_t GetDimColor() override;
};

}; // namespace Loader

#endif // __NUMPY_HPP__
