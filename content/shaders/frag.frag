#version 460 core

out vec4 FragColor;
in vec4 a_color;
in vec2 a_texCoord;

uniform sampler2D u_texture0;

void main()
{
	FragColor = a_color * texture(u_texture0, a_texCoord);
}