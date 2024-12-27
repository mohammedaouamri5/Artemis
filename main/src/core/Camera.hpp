#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
//

namespace CORE {

class Camera {
private:
  enum MODE {
    IMGUI, MANUAL
  };
  enum MODE mode = IMGUI; 
  glm::vec3 position;
  GLuint viewLoc;
  GLuint projectionLoc;
  float yaw = 0;
  float pitch = 0;
  double mouse_x;
  double mouse_y;
  float sensitivity;
  glm::vec3 forward;
  glm::vec3 up;
  glm::vec3 right;
  int speed;
  float fov;
  float near_plane;
  float far_plane;
  GLFWwindow *window;
  int width;
  int height;
  float aspect_ratio = 0.1f;

public:
  glm::mat4x4 view_mat;
  glm::mat4x4 projection_mat;

  Camera(glm::vec4 startpos, GLFWwindow *win, int h, int w);

  void updateCameraVectors();
  void debugCamera() const;

  inline void moveCamera();
  inline void updateRotation();
  inline void updateProjection();
  inline void ImGuiEditor();
  void INIT() ;
  void RUN() ;
};

} // namespace CORE
#endif // CAMERA_HPP
