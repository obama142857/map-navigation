```glsl
#version 330 core
    out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 b =texture(texture2, TexCoord);
    vec4 color = texture(texture1, TexCoord);
    if(color.x>0.7&&color.y<0.2&&color.z>0.7)
    {
        color.x-=0.4;
        color.y+=0.4;
        color.z-=0.4;
    }
    if(b.r<0.1)
        FragColor = color;
    else
    	FragColor = mix(texture(texture1, TexCoord),b,0.5);
    
}
```

