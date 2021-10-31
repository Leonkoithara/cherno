#shader vertex
#version 330 core
layout (location = 0) in vec4 position;
uniform mat4 u_projection;
void main()
{
	gl_Position = u_projection * position;
};

#shader fragment
#version 330 core
uniform vec2 u_view_dim;
uniform float u_radius;
out vec4 outColor;
void main()
{
	float x = (gl_FragCoord.x - u_view_dim.x / 2.0f) / (u_view_dim.x / 2.0f);
	float y = (gl_FragCoord.y - u_view_dim.y / 2.0f) / (u_view_dim.y / 2.0f);
	float len = sqrt(x * x + y * y);
	if (len > u_radius) {
	   discard;
	}

	outColor = vec4(0.0, 1.0, 0.0, 1.0);
}