
#include "CubeLayout.hpp"
#include <core/LOG.hpp>
#include <core/Win.hpp>

#include "traingel.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <spdlog/sinks/stdout_color_sinks.h> // For colored output
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char **argv) {

  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
  CORE::Win *win = new CORE::Win();
  // win->ADD((CORE::Layout *)new PLY(argv[1]));
  // win->ADD((CORE::Layout *)new Traingel());
  win->ADD((CORE::Layout *)new CubeLayout("W0W"));
  win->INIT();
  win->RUN();
  win->CLOSE();
  return 0;
}
