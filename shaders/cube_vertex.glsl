// traingel_vertex.glsl
#version 460 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;

out vec4 vertexColor;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * aPos;
    vertexColor = aColor;
}

