#version 400

layout(points) in;
layout(line_strip, max_vertices = 2) out;

in VS_OUT {
    vec2 normal;
} gs_in[];

void main() {
    gl_PointSize = 20.0;

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = vec4(gs_in[0].normal, 0.0f, 1.0f);
    EmitVertex();



    EndPrimitive();
}