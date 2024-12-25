#include "glad/glad.h"

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

  glm::vec4 pos ={0,0,0,1};

  
  CORE::Win *win = new CORE::Win();
  win->INIT();

  plyobject test("/home/omni/Desktop/me/Artemis/main/src/assets/untitled.ply");


// NOTE : make sure to never declare a shader before initializing the window 
// cause open gl needs the render context in this case glfw
// consult this for more information : 
// https://stackoverflow.com/questions/5724578/why-does-this-opengl-shader-segmentation-fault-on-calls-to-glcreateshader

  shader_program shader("/home/omni/Desktop/me/Artemis/main/src/shaders/basicvertex.art","/home/omni/Desktop/me/Artemis/main/src/shaders/basicfragment.art");
  camera cam(pos,win->Return_ptr(),win->height,win->width,shader.program); 
 

  voxeloid obj({0,0,1} , test.get_vao() , test.vertices_count , shader.program);
  

  win->ADD((CORE::Layout *) &obj );
  win->ADD((CORE::Layout *) &cam );


  win->RUN();


  return 0;
}
