#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 colour;
uniform float position_offset;
void main()
{
colour = color;
gl_Position = vec4(position.x + position_offset , -position.y, position.z, 1.0);
}