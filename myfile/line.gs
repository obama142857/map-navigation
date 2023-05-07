```glsl
#version 330 core

layout (lines) in;
layout (line_strip, max_vertices = 2) out;
in VS_OUT {
    vec3 mypos;
    float mytime;
    int id;
    int sum;
    float scale;
}gs_in[];
out vec3 mypos2;
void main() {
    float t = gs_in[0].mytime;
    vec3 c1 = gs_in[0].mypos;
    vec3 c2 = gs_in[1].mypos;
    float a = gs_in[0].id+1;
    float b = gs_in[1].id+1;
    float s = gs_in[0].sum+1;
    
    vec3 start = gl_in[0].gl_Position.xyz; 
    vec3 end = gl_in[1].gl_Position.xyz;
    vec3 pingyi = normalize(cross(end-start, vec3(0,0,1)));
    float ss = gs_in[0].scale;
    gl_Position = gl_in[0].gl_Position+vec4(pingyi*0.05*ss,0.0);
    
    vec3 color1 = vec3(0.4,1,0.4);
    vec3 color2 = vec3(0, 0.8, 1.0);
    
    if(((a-1)/s<t)&&((a+1)/s>t))
    {
        mypos2=(color1-color2)*cos((t-a/s)*1.5708*s)+color2;
    }
    else
        mypos2 = color2;
    EmitVertex();
   
    gl_Position = gl_in[1].gl_Position+vec4(pingyi*0.05*ss,0.0);
     if((b-1)/s<t&&(b+1)/s>t)
    {
        mypos2=(color1-color2)*cos((t-b/s)*1.5708*s)+color2;
    }
    else
        mypos2 = color2;
    EmitVertex();

    EndPrimitive();

}
```

