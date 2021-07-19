#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


uniform mat4 _mat4 = mat4(1.0f);
uniform vec3 _color = vec3(1.0f, 0.5f, 0.2f);
out vec3 fColor;
out vec2 TexCoord;


void main()
{
    gl_Position = _mat4 * vec4(aPos, 1.0);
    fColor = _color;
    TexCoord = aTexCoord;
}