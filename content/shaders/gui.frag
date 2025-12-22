#version 460 core

out vec4 FragColor;
in vec4 a_color;
in vec2 tex_coord;

uniform sampler2D tex;

void main()
{
	FragColor = a_color * texture(tex * tex_coord);
}