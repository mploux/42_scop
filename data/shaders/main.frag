#version 400 core

out	vec4 out_color;

uniform sampler2D tex;

in vec3 frag_pos;
in vec3 v_normal;
in vec2 v_texcoord;

void main()
{
	float fog = 1.0 / distance(frag_pos, vec3(0,0,0)) * 1;
	if (fog > 1)
		fog = 1;
	if (fog < 0)
		fog = 0;
	vec4 texture_color = texture(tex, v_texcoord);
	out_color = texture_color * fog * dot(vec3(0, 0, -1), v_normal);
}
