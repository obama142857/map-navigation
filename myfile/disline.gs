```glsl
#version 330 core
   layout (lines) in;
layout (line_strip, max_vertices = 2) out;
uniform vec2 mypos1;
uniform vec2 mypos2;
void main() {
    gl_Position =vec4(mypos1,0.0,1.0);
    EmitVertex();
    gl_Position = vec4(mypos2,0.0,1.0);
    EmitVertex();
    EndPrimitive();
}
```
