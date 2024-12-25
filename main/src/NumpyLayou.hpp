

#ifndef __NUMPY_LAYOUT_HPP__
#define __NUMPY_LAYOUT_HPP__

#include "Layout.hpp"
#include <Loader/Numpy.hpp>
#include <vector>
#include <VAOLayer.hpp>
class NumpyLayout : public CORE::Layout {

  Loader::Numpy *numpy = nullptr;
  char *path = nullptr;
  int path_size = 100;
  float __fov; 
  float threshold = 0.0001f;
  std::vector<Layout*> VAOs; 
  std::vector<bool> RUNss; 

  void ReAllocatePath();
  void ReAllocateNnmpy();

public:

  void INIT() override;
  void RUN() override;
  void DIST() override;
};

#endif
