#version 330 core
out vec4 color;
in vec3 colour;
void main()
{
color = vec4(colour, 1.0f);
}