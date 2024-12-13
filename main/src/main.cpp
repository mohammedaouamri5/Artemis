#include "traingel.hpp"
#include "core/Win.hpp"
#include "ply.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
  CORE::Win *win = new CORE::Win();
  win->ADD((CORE::Layout *)new PLY("untitled.ply"));
  // win->ADD((CORE::Layout *)new Traingel());
  win->INIT();
  win->RUN();
  win->CLOSE();
  return 0;
}
