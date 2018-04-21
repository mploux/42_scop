#version 400 core

out	vec4 out_color;

uniform sampler2D tex;

uniform float use_texcoord;
uniform float use_texture;
uniform float use_normal;

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
	vec4 texture_poscoord = texture(tex, v_position.yz);
	vec4 texture_texcoord = texture(tex, texcoord);
	vec4 vertex_color = vec4(v_color * 0.5, 1.0);
	float light = dot(vec3(0, 0, -1), v_normal);

	vec4 final_texture = mix(texture_poscoord, texture_texcoord, use_texture);
	vec4 final_color = mix(vertex_color, final_texture, use_texture);
	float final_light = mix(1.0, light, use_normal);
	out_color = final_color * fog * final_light;
}
