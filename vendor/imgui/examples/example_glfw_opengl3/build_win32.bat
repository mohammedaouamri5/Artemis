#!/bin/bash

# Build for g++ compiler.

OUT_DIR=Debug
OUT_EXE=example_glfw_opengl3
INCLUDES="-I../.. -I../../backends -I../../libs/glfw/include"
SOURCES="main.cpp ../../backends/imgui_impl_glfw.cpp ../../backends/imgui_impl_opengl3.cpp ../../imgui*.cpp"
LIBS="-L../../libs/glfw/lib-vc2010-32 -lglfw3 -lopengl32 -lgdi32 -lshell32"

mkdir -p $OUT_DIR
g++ -g -std=c++11 -m32 $INCLUDES $SOURCES -o $OUT_DIR/$OUT_EXE $LIBS
