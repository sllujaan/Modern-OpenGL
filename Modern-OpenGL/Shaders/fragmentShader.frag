#version 330 core

in vec3 fColor;
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(fColor, 0.1f);  //vec4(fColor, 1.0f);
} 