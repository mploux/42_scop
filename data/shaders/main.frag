#version 400 core

out	vec4 out_color;

uniform sampler2D tex;

uniform int use_texcoord;
uniform float use_texture;

in vec3 frag_pos;
in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;
in vec3 v_color;

void main()
{
	float fog = 1.0 / distance(frag_pos, vec3(0,0,0)) * 5;
	if (fog > 1)
		fog = 1;
	if (fog < 0)
		fog = 0;
	vec2 texcoord = v_position.yz;
	if (use_texcoord == 1)
		texcoord = v_texcoord;
	vec4 texture_color = texture(tex, texcoord);
	vec4 vertex_color = vec4(v_color * 0.5, 1.0);
	vec4 final_color = mix(vertex_color, texture_color, use_texture);
	out_color = final_color * fog;// * dot(vec3(0, 0, -1), v_normal);
}
