#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D mytexture;

void main()
{
    FragColor = vec4(texture(mytexture,TexCoord).xyz,0.5f);
}