#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 _mat4 = mat4(1.0f);

void main()
{
    gl_Position = _mat4 * vec4(aPos, 1.0);
}