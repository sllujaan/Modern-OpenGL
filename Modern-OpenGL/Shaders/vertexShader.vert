#version 400

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 aNormal;

out VS_OUT {
    vec2 normal;
} vs_out;

void main() {
    gl_Position = vec4(vp, 0.0, 1.0);
    vs_out.normal = aNormal;
}