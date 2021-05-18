#version 330 core

layout (location = 0) in vec2 aPos;


void main()
{
    gl_Position = vec4(aPos.x + 2.4, aPos.y + 2.4, 0.0, 1.0);
}