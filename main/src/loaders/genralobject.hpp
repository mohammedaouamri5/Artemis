#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext/vector_float4.hpp"
#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

class object {

  protected:
    glm::vec3 position;
    float *vertices;
    unsigned int *faces;
    unsigned int vao;

    virtual void initialize_buffers(){};


};
