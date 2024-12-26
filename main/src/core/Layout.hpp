

#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include "Camera.hpp"
namespace CORE {

class Layout {
public:
  static Camera* camera;
  virtual void INIT() {};
  virtual void RUN() {};
  virtual void DIST() {};
};
} // namespace CORE

#endif // _LAYOUT_H_
