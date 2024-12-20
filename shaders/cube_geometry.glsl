// traingel_geometry.glsl
#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 v_color[];
out vec4 g_color;

void main() {
    vec4 avgColor = (v_color[0] + v_color[1] + v_color[2]) / 3.0;
    for (int i = 0; i < 3; i++) {
        g_color = avgColor;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
