#version 400

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 aNormal;


void main() {
    gl_Position = vec4(vp, 0.0, 1.0);
}