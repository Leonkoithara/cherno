#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tex_coords;

out vec2 v_tex_coords;

void main()
{
	gl_Position = position;
	v_tex_coords = tex_coords;
};

#shader fragment
#version 330 core

in vec2 v_tex_coords;

layout (location = 0) out vec4 color;

uniform sampler2D u_texture;

void main()
{
	vec4 tex_color = texture(u_texture, v_tex_coords);
	color = tex_color;
};