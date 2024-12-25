
#ifndef _WIN_H_
#define _WIN_H_

#include "Layout.hpp"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <core/Font.hpp>
#include <optional>
#include <vector>
namespace CORE {

class Win {
public:
  Win() :  font("assist/fonts/FiraCodeNerdFontMono-Regular.ttf", 32.0f) {} 
  void INIT();
  int INIT_LOOP();
  void RUN();
  void ADD(Layout *layout) { Layouts.push_back(layout); }
  void CLEAR_LOOP();
  void CLOSE();

private:
  CORE::Font font; // ("fonts/FiraCodeNerdFontMono-Regular.ttf", 32.0f);
  std::vector<Layout *> Layouts{};
  GLFWwindow *window;
};

} // namespace CORE

#endif // _WIN_H_
