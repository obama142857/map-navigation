#version 330 core
out vec4 FragColor;

in vec4 myPosition;

uniform vec3 ourColor;
uniform float r;
uniform vec2 mypos;

void main()
{

float a = myPosition.x*800+800;
float b = myPosition.y*450+450;
float c = (a-mypos.x)*(a-mypos.x)+(b-mypos.y)*(b-mypos.y);
vec4 aa = vec4(ourColor,0.8);
if(c>r*r)
discard;

   FragColor = aa;
};