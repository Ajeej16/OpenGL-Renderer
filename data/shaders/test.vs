#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv;

out vec3 normal;
out vec3 frag_pos;
out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection*view*model*vec4(pos, 1.0);

	normal = mat3(transpose(inverse(model))) * norm;
	frag_pos = vec3(model*vec4(pos, 1.0));

	tex_coords = uv;	
}