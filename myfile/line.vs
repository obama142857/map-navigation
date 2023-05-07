```glsl
#version 330 core
layout (location = 0) in vec2 aPos;
out VS_OUT{
    vec3 mypos;
    float mytime;
    int id;
    int sum;
    float scale;
} vs_out;
uniform float time1;
uniform int mysum;
uniform mat4 model;
uniform float sc;
void main()
{
    float a = aPos.x * 2 * 6.016 - 6.016;
    float b =aPos.y * 2 * 7.68 - 7.68;
    gl_Position = model*vec4(a, b, 0.0, 1.0); 
    vs_out.mypos = vec3(aPos.x,aPos.y,0);
    vs_out.mytime = time1;
    vs_out.id = gl_VertexID;
    vs_out.sum = mysum;
    vs_out.scale = sc;
}
```