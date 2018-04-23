#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texcoord;
layout (location = 2) in vec3 in_normal;
layout (location = 3) in vec3 in_color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 frag_pos;
out vec3 v_position;
out vec3 v_normal;
out vec2 v_texcoord;
out vec3 v_color;

void main()
{
	v_position = in_position;
	v_normal = (modelMatrix * vec4(in_normal, 0.0)).xyz;
	v_texcoord = in_texcoord;
	v_color = in_color;
	frag_pos = (modelMatrix * vec4(in_position, 1.0)).xyz;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);
}
