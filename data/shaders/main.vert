#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normals;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 frag_pos;
out vec3 v_normals;

void main()
{
	v_normals = (viewMatrix * vec4(in_normals, 0.0)).xyz;
	frag_pos = (viewMatrix * vec4(in_position, 1.0)).xyz;
	gl_Position = projectionMatrix * viewMatrix * vec4(in_position, 1.0);
}
