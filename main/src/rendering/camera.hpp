#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

class camera : public CORE::Layout {
  private:
    glm::vec3 position;

    double yaw =0;
    double pitch =0;

    double mouse_x;
    double mouse_y;

    float sensitivity ;
    glm::vec3 forward;
    glm::vec3 up  ;
    glm::vec3 right;

    int speed ;
// perspective matrix attributes
    float fov ;
    float near_plane ;
    float far_plane ;

    GLFWwindow *window;
    int width;
    int height;
    float aspect_ratio =0.1;



  public:

    glm::mat4x4 view_mat;
    glm::mat4x4 projection_mat;

void updateCameraVectors(void) {
    // Create the forward vector based on yaw and pitch angles

    // Apply yaw and pitch directly in radians
    forward.x = cos(yaw) * cos(pitch);  // yaw affects x and z
    forward.y = sin(pitch);              // pitch affects y
    forward.z = sin(yaw) * cos(pitch);   // yaw affects x and z

    // Normalize the forward vector
    //forward = glm::normalize(forward);

    // Recalculate the right vector (cross product of forward and global up)
    right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));  // Right vector is perpendicular to forward and up

    // Update the view matrix (up vector is fixed)
    view_mat = glm::lookAt(position, position + forward, up);
}

  

    void debugCamera() const {
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
    std::cout << "Yaw: " << yaw << " Pitch: " << pitch << "\n";
    std::cout << "Forward: (" << forward.x << ", " << forward.y << ", " << forward.z << ")\n";
    std::cout << "Right: (" << right.x << ", " << right.y << ", " << right.z << ")\n";
    std::cout << "Up: (" << up.x << ", " << up.y << ", " << up.z << ")\n";

    std::cout << "View Matrix:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << view_mat[i][0] << " " << view_mat[i][1] << " "<< view_mat[i][2] << " "<< view_mat[i][3] <<"\n";
         
    }
    std::cout << "projection Matrix:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << projection_mat[i][0] << " " << projection_mat[i][1] << " "<< projection_mat[i][2] << " "<< projection_mat[i][3] <<"\n";
         
    }
    }




    void moveCamera() {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position.z -= 1 ; // Move forward
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position.z += 1; // Move backward
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position.x -= 1; // Move left
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position.x += 1 ; // Move right
        }
    }

    camera(glm::vec4 startpos ,GLFWwindow *win ,int h ,int w)
        : position(startpos),window(win) ,height(h) ,width(w){

      mouse_x =0;
      mouse_y =0;

      sensitivity = 5;
      forward={0,0,-1};
      up = {0,1,0};
      right={1,0,0};

      speed =1;
// perspective matrix attributes
      fov =45.0f;
      near_plane =0.1f;
      far_plane =100.0f;
      aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
      projection_mat = glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);

        }

    void updateRotation() {
      glfwGetCursorPos(window, &mouse_x, &mouse_y);

      static double old_x =0;
      static double old_y =0;

// if mouse didn't move then there's no need to calculate
      if(old_x+old_y != mouse_x+mouse_y){

// since mouse_x/width gives us outputs from range 0 to 1 so we do ((mouse_x/width) -.5)*2
// to normalize it into [-1,1] so we can calculate degrees with no problem
        
// NOTE: yaw and pitch are in radians
        yaw = (asin(( mouse_x/width -.5) *2)) ;
        pitch = (asin((mouse_y/height -.5 ) *2));

        old_x = mouse_x;
        old_y = mouse_y;

//for debugging
      //std::cout <<"yaw :"<< yaw<<"\npitch :"<<pitch<<"\n";

        }
    }


    void INIT() override{

    }

    void RUN() override{

      updateRotation();
      moveCamera();
      updateCameraVectors();
      debugCamera();


    }

};
