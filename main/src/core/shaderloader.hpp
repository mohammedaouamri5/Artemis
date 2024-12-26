
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

class shader_program {
private:
    char* vss;
    char* fss;
    unsigned int program;

    unsigned int CompileShader(unsigned int type, char* src);
    void CreateShader(char* vertexShader, char* fragmentShader);
    char* read_source(const char* file_path);

public:
    shader_program(const char* vertexpath, const char* fragmentpath);
    ~shader_program();

    unsigned int getProgram() const { return program; }
};
