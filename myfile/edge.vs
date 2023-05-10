```glsl
#version 330 core
layout (location = 0) in vec2 aPos;
uniform mat4 model;
void main()
{
    float a = aPos.x * 2 * 6.016 - 6.016;
    float b =aPos.y * 2 * 7.68 - 7.68;
    gl_Position = model*vec4(a, b, 0.0, 1.0); 
}
```