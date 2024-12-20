// traingel_vertex.glsl
#version 460 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;

out vec4 v_color;

void main() {
    v_color = aColor;
    gl_Position = aPos;
}
