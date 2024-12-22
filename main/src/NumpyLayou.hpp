

#ifndef __NUMPY_LAYOUT_HPP__
#define __NUMPY_LAYOUT_HPP__

#include "Layout.hpp"
#include <Loader/Numpy.hpp>
class NumpyLayout : public CORE::Layout {

  Loader::Numpy *numpy = nullptr;
  char *path = nullptr;
  int path_size = 100;

  void ReAllocatePath();
  void ReAllocateNnmpy();

public:

  void INIT() override;
  void RUN() override;
  void DIST() override;
};

#endif
