#include "Loader/cube.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <Loader/Numpy.hpp>
#include <cmath>
#include <cnpy.h>
#include <core/Shader.hpp>
#include <cstdint>
#include <cstdio>
#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::perspective and glm::lookAt
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr (optional)
#include <strings.h>

#define __UP__(x, y) x - 1, y
#define __DOWN__(x, y) x + 1, y
#define __LEFT__(x, y) x, y - 1
#define __RIGHT__(x, y) x, y + 1

namespace Loader {

uint64_t Numpy::GetDimVertices() { return 4; }
float *Numpy::GetVertices() { return &Vertex[0]; }
uint64_t Numpy::GetNbVertices() { return Vertex.size() / GetDimVertices(); }
uint64_t Numpy::GetSizeVertices() {

  LOG_INFO(" Vertex.size() * sizeof(float)  =  {}",
           Vertex.size() * sizeof(float));
  LOG_INFO(" Vertex.size()                  =  {}", Vertex.size());
  LOG_INFO("                sizeof(float)   =  {}", sizeof(float));

  return Vertex.size() * sizeof(float);
}

uint64_t Numpy::GetDimColor() { return 4; }
float *Numpy::GetColor() { return &Color[0]; }
uint64_t Numpy::GetNbColor() { return Color.size() / GetDimColor(); }
uint64_t Numpy::GetSizeColor() { return Color.size() * sizeof(float); }

uint64_t Numpy::GetDimIndices() { return 1; }
unsigned int *Numpy::GetIndices() { return &Indices[0]; }
uint64_t Numpy::GetNbIndices() { return Indices.size(); }
uint64_t Numpy::GetSizeIndices() {
  return Indices.size() * sizeof(unsigned int);
}
Numpy::Numpy(const char *__path, float __fov, float __threshold) {
  LOG_INFO("WOW {}", __path);

  this->path = (char *)__path;
  LOG_WARN("Change the path");

  this->m_data = cnpy::npy_load("IMG.npy");
  this->data = this->m_data.as_vec<float>();

  C = this->m_data.shape[0];
  H = this->m_data.shape[1];
  W = this->m_data.shape[2];
  fov = __fov;
  tan_rad_fov = glm::tan(glm::radians(fov));
  this->threshold = __threshold;

  // FIXME : ADD THREADS
  for (int x = 0; x < H; x++) /* GO DOWN */ {
    for (int y = 0; y < W; y++) /* GO RIGHT */ {
      glm::vec4 __result = Point(x, y, data[Index(3, x, y)]);
      Vertex.push_back(__result.x);
      Vertex.push_back(__result.y);
      Vertex.push_back(__result.z);
      Vertex.push_back(1);
      Color.push_back(data[Index(0, x, y)]);
      Color.push_back(data[Index(1, x, y)]);
      Color.push_back(data[Index(2, x, y)]);
      Color.push_back(data[Index(3, x, y)]);
    }
  }
}

inline int Numpy::Index(int i, int x, int y) { return i * H * W + x * W + y; }

glm::vec4 Numpy::Point(int x, int y, float z) {
  glm::vec4 __result(0, 0, z, 1);
  __result.x = (float(x - (x / H)) / H) * __result.z * tan_rad_fov;
  __result.y = (float(y - (y / W)) / W) * __result.z * tan_rad_fov;
  return __result;
}

void Numpy::AddFace(unsigned int First, unsigned int Second,
                    unsigned int Third) {
  Indices.push_back(First - Index(3, 0, 0));
  Indices.push_back(Second - Index(3, 0, 0));
  Indices.push_back(Third - Index(3, 0, 0));
}

void Numpy::Mesh() {
  float threshold = 0.1f;
  LOG_INFO("X then Y");
  // FIXME : ADD THREADS
  glm::vec4 UP = Point(__UP__(1, 1), data[Index(3, __UP__(1, 1))]);
  for (int x = 1; x < H; x++) /* GO DOWN */ {
    glm::vec4 LEFT = Point(__LEFT__(1, 1), data[__LEFT__(1, 1)]);
    for (int y = 1; y < W; y++) /* GO RIGHT */ {
      glm::vec4 RIGHT = Point(__RIGHT__(x, y), data[Index(3, __RIGHT__(x, y))]);
      glm::vec4 DOWN = Point(__DOWN__(x, y), data[Index(3, __DOWN__(x, y))]);
      glm::vec4 INDEX = Point(x, y, data[Index(3, x, y)]);
      {
        if (glm::distance(UP, INDEX) < this->threshold &&
            glm::distance(LEFT, INDEX) < threshold)
          AddFace(Index(3, x, y), Index(3, __UP__(x, y)),
                  Index(3, __LEFT__(x, y)));

        if (glm::distance(DOWN, INDEX) < this->threshold &&
            glm::distance(RIGHT, INDEX) < threshold)
          AddFace(Index(3, x, y), Index(3, __DOWN__(x, y)),
                  Index(3, __RIGHT__(x, y)));
      }
      LEFT = INDEX;
    }
    UP = Point(__UP__(x, 1), data[Index(3, __UP__(x, 1))]);
  }
}

void Numpy::INIT_THE_DROW(unsigned int *VAO, CORE::Shader *program,
                          uint64_t *NbIndices) /* override */ {
  *NbIndices = GetNbIndices();
  unsigned int VBO, CBO, EBO;
  // Generate and bind Vertex Array Object (VAO)
  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);

  // Generate and bind Vertex Buffer Object (VBO) for vertex positions
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, this->GetSizeVertices(), this->GetVertices(),
               GL_STATIC_DRAW);

  // Set vertex attribute pointer for positions (location = 0)
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Verify VBO size
  int VBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &VBO_size);
  if (VBO_size != this->GetSizeVertices()) {
    LOG_CRITICAL("VBO size mismatch");
  }

  // Generate and bind Color Buffer Object (CBO) for vertex colors
  glGenBuffers(1, &CBO);
  glBindBuffer(GL_ARRAY_BUFFER, CBO);
  glBufferData(GL_ARRAY_BUFFER, this->GetSizeColor(), this->GetColor(),
               GL_STATIC_DRAW);

  // Set vertex attribute pointer for colors (location = 1)
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // Verify CBO size
  int CBO_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &CBO_size);
  if (CBO_size != this->GetSizeColor()) {
    LOG_CRITICAL("CBO size mismatch");
  }

  // Generate and bind Element Buffer Object (EBO) for indices
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->GetSizeIndices(),
               this->GetIndices(), GL_STATIC_DRAW);

  // Unbind VAO (optional, good practice)
  glBindVertexArray(0);

  // Initialize shaders
  CORE::Shader vertexShader("assist/shaders/numpy_vertex.glsl",
                            glCreateShader(GL_VERTEX_SHADER));
  CORE::Shader fragmentShader("assist/shaders/numpy_fragment.glsl",
                              glCreateShader(GL_FRAGMENT_SHADER));

  // Load, compile, and check vertex shader
  vertexShader.GLshaderSource();
  vertexShader.GLcompileShader();
  vertexShader.checkShaderCompileStatus();

  // Load, compile, and check fragment shader
  fragmentShader.GLshaderSource();
  fragmentShader.GLcompileShader();
  fragmentShader.checkShaderCompileStatus();

  // Create and link shader program
  *program = CORE::Shader("", glCreateProgram());
  glAttachShader(program->getShader(), vertexShader.getShader());
  glAttachShader(program->getShader(), fragmentShader.getShader());
  glLinkProgram(program->getShader());
  program->checkProgramLinkingStatus();

  // Clean up shader objects after linking
  glDeleteShader(vertexShader.getShader());
  glDeleteShader(fragmentShader.getShader());
}

} // namespace Loader
