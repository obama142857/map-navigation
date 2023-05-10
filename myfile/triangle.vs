```glsl
#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 myPosition;

uniform mat4 model;

void main()
{
gl_Position = model*vec4(aPos, 1.0);
};
```

