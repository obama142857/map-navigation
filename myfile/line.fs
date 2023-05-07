```glsl
#version 330 core
out vec4 FragColor;
in vec3 mypos2;
void main()
{
    FragColor = vec4(mypos2, 0.7);   
}
```