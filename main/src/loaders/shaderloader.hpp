#pragma once

#include <glad/glad.h>

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <glad/glad.h>
#include <string>
#include <utility>
#include <fmt/base.h>


#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

#include <GLFW/glfw3.h>



class shader_program{
  private:

    char *vss;
    char *fss;

    unsigned int CompileShader(unsigned int type, char* src) {
      unsigned int id = glCreateShader(type);
      glShaderSource(id, 1, &src, nullptr);
      glCompileShader(id);

        // Error handling
      int result;
      glGetShaderiv(id, GL_COMPILE_STATUS, &result);
      if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader!" << std::endl;
        std::cerr << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
        }

    return id;
    }

    void CreateShader(char* vertexShader, char* fragmentShader) {

        this->program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(this->program, vs);
        glAttachShader(this->program, fs);
        glLinkProgram(this->program);
        glValidateProgram(this->program);

        glDeleteShader(vs);
        glDeleteShader(fs);
    
        printf("compiled shaders succesfully.\n");

    }

    char * read_source(const char* file_path){
        printf("i started.\n");

        std::ifstream file(file_path, std::ios::in | std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << file_path << std::endl;
            return nullptr;
        }

        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        char* content = new char[static_cast<std::size_t>(fileSize) + 1];
        file.read(content, fileSize);
        content[fileSize] = '\0';

        file.close();
        return content;
    }

  public:

    unsigned int program;

    shader_program(const char* vertexpath , const char* fragmentpath){
      vss = read_source(vertexpath);
      fss = read_source(fragmentpath);
      if(vss == NULL || fss == NULL){
        printf("error loading shader source files.\n");
        exit(1);
      }

      printf("loaded:\n%s\n%s\n succesfully.\n",vertexpath,fragmentpath);
      
      CreateShader(vss,fss);
      printf("shaders created succesfully.\n");


    }

    ~shader_program() {
        glDeleteProgram(program);
    }
};
