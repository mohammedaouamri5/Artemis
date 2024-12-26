#include "Inspector.hpp"
#include "Loader/Numpy.hpp"
#include "Loader/cube.hpp"
#include "VAO.hpp"
#include "glad/glad.h"
#include "imgui.h"

#include <Camera.hpp>
#include <Win.hpp>
// #include "loaders/plyobject.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <shaderloader.hpp>

#include <cstdio>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CORE::Camera *CORE::Layout::camera = nullptr; // Define the static member

int main() {
  glm::vec4 pos = {0, 0, 0, 1};

  CORE::Win *win = new CORE::Win();
  win->INIT();


  // NOTE : make sure to never declare a shader before initializing the window
  // cause open gl needs the render context in this case glfw
  // consult this for more information :
  // https://stackoverflow.com/questions/5724578/why-does-this-opengl-shader-segmentation-fault-on-calls-to-glcreateshader

  win->ADD(new Inspector());
  win->ADD(new VAO(glm::vec4(0.f), new Loader::Cube()));
  win->ADD(new VAO(glm::vec4(0.f), new Loader::Numpy("c<nqd",23,23)));
  win->RUN();

  return 0;
}
