
#ifndef _WIN_H_
#define _WIN_H_

#include "Layout.hpp"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <vector>
namespace CORE {

class Win {
public:
  void INIT();
  int INIT_LOOP();
  void RUN();
  void ADD(Layout *layout) { Layouts.push_back(layout); }
  void CLEAR_LOOP();
  void CLOSE();

private:
  std::vector<Layout *> Layouts{};
  GLFWwindow *window;
};

} // namespace CORE

#endif // _WIN_H_
