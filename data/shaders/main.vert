#version 400 core

layout (location = 0) in vec3 in_position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 frag_pos;

void main()
{
	frag_pos = (viewMatrix * vec4(in_position, 1.0)).xyz;
	gl_Position = projectionMatrix * viewMatrix * vec4(in_position, 1.0);
}
