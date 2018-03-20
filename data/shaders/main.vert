#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_texcoord;
layout (location = 2) in vec3 in_normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 frag_pos;
out vec3 v_normal;
out vec3 v_texcoord;

void main()
{
	v_normal = (viewMatrix * vec4(in_normal, 0.0)).xyz;
	v_texcoord = (viewMatrix * vec4(in_texcoord, 0.0)).xyz;
	frag_pos = (viewMatrix * vec4(in_position, 1.0)).xyz;
	gl_Position = projectionMatrix * viewMatrix * vec4(in_position, 1.0);
}
