#version 330 core
out vec4 color;
in vec4 vertex_color;
in vec2 texture_coord;
uniform sampler2D ourTexture1, ourTexture2;
void main()
{
color = mix(texture(ourTexture1, texture_coord), texture(ourTexture2,texture_coord),0.5);
}