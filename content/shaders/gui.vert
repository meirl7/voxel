#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;

out vec4 a_color;
out vec2 tex_coord;

uniform mat4 pvm;

void main()
{
	tex_coord = v_texCoord;
	gl_Position = pvm * vec4(v_position, 1.0);
}