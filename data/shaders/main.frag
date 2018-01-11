#version 400 core

out	vec4 out_color;

in vec3 frag_pos;
in vec3 v_normals;

void main()
{
	float fog = 1.0 / distance(frag_pos, vec3(0,0,0)) * 1;
	if (fog > 1)
		fog = 1;
	if (fog < 0)
		fog = 0;
	out_color = vec4(1, 1, 0, 1) * fog * dot(vec3(0, 0, 1), v_normals);
}
