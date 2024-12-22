#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::perspective and glm::lookAt
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr (optional)
#include <eigen3/Eigen/QR> // or any other necessary Eigen header
#include "Loader/cube.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/matrix.hpp"
#include <Loader/Numpy.hpp>
#include <cnpy.h>
#include <cstdint>
#include <cstdio>

namespace Loader {

Numpy::Numpy(const char *__path) {
  LOG_INFO("WOW {}", __path);

  this->path = (char *)__path;
  LOG_WARN("Change the path");

  this->m_data = cnpy::npy_load("IMG.npy");
  this->data = this->m_data.as_vec<float>();

  C = this->m_data.shape[0];
  H = this->m_data.shape[1];
  W = this->m_data.shape[2];
}
int Numpy::Index(int i, int ii, int iii) { return i * H * W + ii * W + iii; }
void Numpy::Mesh() {

  LOG_INFO("START LOGGING");
  // glm::mat4 projection = glm::perspective(glm::radians(45.0f), // Field of
  // view
  //                                         1.,                  // Aspect
  //                                         ratio 0.1f,  // Near clipping plane
  //                                         100.0f // Far clipping plane
  // );

  glm::mat4 glm_projection = glm::perspective(glm::radians(120.f), // Field of view
                                          1.0f,                // Aspect ratio
                                          0.1f,  // Near clipping plane
                                          100.0f // Far clipping plane
  );

      Eigen::Matrix4f eigenMatrix;

    // Convert GLM matrix to Eigen matrix
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            eigenMatrix(i, j) = glm_projection [i][j];
        }
    }


  LOG_INFO("The Projection that  the camera do :\n{}",
           glm::to_string());

  return;
  for (int x = 0; x < H; x++) {
    for (int y = 0; y < W; y++) {
      LOG_INFO("(x, y, z, w) = ({}, {}, {}, {})", x, y, data[Index(3, x, y)],
               0);
      LOG_INFO("(x, y, z, w) = ({}, {}, {}, {})", float(x - (x / H)) / H,
               float(y - (y / W)) / W, data[Index(3, x, y)], 0);
      LOG_WARN("--------");
    }
    printf("\n");
  }
}

} // namespace Loader
