#version 400 core

out	vec4 out_color;

uniform sampler2D tex;

uniform float use_texcoord;
uniform float use_texture;
uniform float use_normal;
uniform float use_specular;
uniform vec3 light_pos;
uniform vec3 camera_pos;

in vec3 frag_pos;
in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;
in vec3 v_color;

void main()
{
	float fog = 1.0 / distance(camera_pos, frag_pos) * 5;
	if (fog > 1)
		fog = 1;
	if (fog < 0)
		fog = 0;
	vec2 texcoord = v_position.yz;
	vec4 texture_poscoord = texture(tex, v_position.yz);
	vec4 texture_texcoord = texture(tex, v_texcoord);
	vec4 vertex_color = vec4(v_color * 0.5, 1.0);

	vec3 light_color = vec3(1, 1, 1);
	float light_intensity = 1.0 / distance(frag_pos, light_pos) * 5;
	vec3 light = dot(normalize(frag_pos - light_pos), -v_normal) * light_intensity * light_color;

	vec4 final_texture = mix(texture_poscoord, texture_texcoord, use_texcoord);
	vec4 final_color = mix(vertex_color, final_texture, use_texture);
	vec3 final_light = mix(vec3(1), light, use_normal);

	vec3 specular = vec3(0);
	if (use_specular > 0)
	{
		vec3 light_dir = normalize(frag_pos - light_pos);
		vec3 cam_dir = normalize(frag_pos - camera_pos);
		vec3 specular_reflect = reflect(-light_dir, v_normal);
		float specular_intensity = clamp(dot(cam_dir, specular_reflect), 0.0, 1.0);
		specular = pow(specular_intensity, 10) * 10 * final_light;
	}

	out_color = final_color * fog * vec4(final_light + specular * use_specular, 1.0);
}
