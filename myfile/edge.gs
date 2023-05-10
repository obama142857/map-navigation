```glsl
#version 330 core
layout (lines) in;
layout (line_strip, max_vertices = 2) out;
out vec3 mypos2;
void main() {
    
    gl_Position = gl_in[0].gl_Position;
    mypos2 = vec3(1,1,0);
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    EndPrimitive();
}
```