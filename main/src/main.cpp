#include <glad/glad.h>
#include "traingel.hpp"
#include "core/Win.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {

    // Create an instance of Traingel and initialize resources
    Traingel triangle;
    CORE::Win * win =  new CORE::Win();
    win->ADD(&triangle);
    win->INIT();
    win->RUN();
    win->CLOSE();
    return 0;
}

