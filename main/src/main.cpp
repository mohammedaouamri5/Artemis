#include "traingel.hpp"
#include "core/Win.hpp"
#include "ply.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include "core/LOG.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> // For colored output


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc , char **argv) {

    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
  CORE::Win *win = new CORE::Win();
  // win->ADD((CORE::Layout *)new PLY(argv[1]));
  win->ADD((CORE::Layout *)new Traingel());
  win->INIT();
  win->RUN();
  win->CLOSE();
  return 0;
}


