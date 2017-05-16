#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;
out vec4 vertex_color;
out vec2 texture_coord;

uniform mat4 transform;
void main()
{
texture_coord = textCoord;
vertex_color = vec4(color,1.0);
gl_Position = transform * vec4(position.x , -position.y, position.z, 1.0);
}