#include "core/Win.hpp"
#include "rendering/camera.hpp"
#include "loaders/plyobject.hpp"
#include "loaders/shaderloader.hpp"
#include "rendering/voxeloid.hpp"

#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {

  shader_program shader("main/src/shaders/basicvertex.art",
                        "main/src/shaders/basicfragment.art");
  // assets is a folder containing the meshes
  plyobject test("assets/untitled.ply");
  
  CORE::Win *win = new CORE::Win();
  
  glm::vec4 pos ={0,0,0,1};
  win->INIT();
  win->ADD((CORE::Layout *)new camera(pos,win->Return_ptr(),win->height,win->width));
  win->ADD((CORE::Layout *)new voxeloid({0,0,0},test.vao,test.vertices_count));


  win->RUN();


  return 0;
}
