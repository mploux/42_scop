/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:03:07 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 18:28:24 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_core		*new_core(char *model, char *texture)
{
	t_core	*c;
	float	scale;

	if (!(c = (t_core *)malloc(sizeof(t_core))))
		error("Malloc error !");
	c->display = init_display("scop - 42 - mploux", 1280, 720);
	c->input = init_input(c->display.window);
	c->camera = init_camera(&c->display, 70.0f, 0.5f, 100.0f);
	c->shader = new_shader("data/shaders/main.vert", "data/shaders/main.frag");
	c->texture = new_texture(texture);
	c->model = new_model(model);
	c->ground = new_model("data/models/plane.obj");
	c->scene = init_scene();
	c->show_ground = 0;
	c->model_pos = vec3(0, 0, 0);
	c->model_rot = vec3(0.0f, 270.0f, 0.0f);
	scale = 3.0f / c->model->max_dim;
	c->model_scale = vec3(scale, scale, scale);
	c->rot_factor = vec3(0, 1, 0);
	c->use_normal = 0;
	c->use_texture = 0;
	c->use_texcoord = 0;
	c->light_pos = c->camera.position;
	c->ground_trs = mat4_translate(vec3(0, -2, 0));
	return (c);
}

void		delete_core(t_core **core)
{
	clean_scene(&(*core)->scene);
	delete_shader(&(*core)->shader);
	delete_mesh(&(*core)->model);
	delete_texture(&(*core)->texture);
	clean_display(&(*core)->display);
	free(*core);
	*core = NULL;
}

void		run_core(t_core *c)
{
	clock_t	before_time;
	clock_t	current_time;

	before_time = clock();
	while (!glfwWindowShouldClose(c->display.window))
	{
		current_time = clock();
		if (current_time - before_time > (double)CLOCKS_PER_SEC / 600.0)
		{
			input_update(&c->input);
			if (get_key_down(&c->input, GLFW_KEY_ESCAPE) && !c->input.focused)
				break ;
			input_handle_focus(&c->input);
			update(c);
			before_time = current_time;
		}
		resize(&c->display, &c->camera);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(c);
		glfwSwapBuffers(c->display.window);
		glfwPollEvents();
	}
}

void		update(t_core *c)
{
	camera_update(&c->camera);
	handle_render_controls(c, 0.05f);
	if (get_key_up(&c->input, GLFW_KEY_3))
		c->show_ground = !c->show_ground;
	if (get_key_up(&c->input, GLFW_KEY_5))
		c->light_pos = c->camera.position;
	if (get_key_up(&c->input, GLFW_KEY_6))
		c->use_specular = 1.0 - c->use_specular;
	if (get_key_up(&c->input, GLFW_KEY_Q))
		scene_add(&c->scene, new_entity(c->model, &c->camera));
	c->model_rot.x += c->rot_factor.x;
	c->model_rot.y += c->rot_factor.y;
	c->model_rot.z += c->rot_factor.z;
	c->model_trs = mat4_transform(c->model_pos, c->model_rot, c->model_scale);
	c->model_centered_trs = mat4_translate(vec3_negate(c->model->center));
	handle_controls(c, 0.1f);
	handle_mouse_controls(c, 0.4f);
	handle_camera_controls(c, 0.1f);
	handle_rotation_controls(c, 0.1f);
}

void		render(t_core *c)
{
	t_mat4	transformation;

	glUseProgram(c->shader->program);
	shader_uniform_16f(c->shader, "projectionMatrix", c->camera.projection);
	shader_uniform_16f(c->shader, "viewMatrix", c->camera.transform);
	shader_uniform_1f(c->shader, "use_texcoord", c->use_texcoord_f);
	shader_uniform_1f(c->shader, "use_texture", c->use_texture_f);
	shader_uniform_1f(c->shader, "use_normal", c->use_normal_f);
	shader_uniform_3f(c->shader, "light_pos", c->light_pos);
	shader_uniform_1f(c->shader, "use_specular", c->use_specular);
	shader_uniform_3f(c->shader, "camera_pos", c->camera.position);
	transformation = mat4_mul(c->model_trs, c->model_centered_trs);
	bind_texture(c->texture);
	transform(&transformation, c->shader);
	draw(c->model);
	scene_render(&c->scene, c->shader);
	if (c->show_ground)
	{
		shader_uniform_1f(c->shader, "use_texcoord", 1.0f);
		shader_uniform_1f(c->shader, "use_texture", 1.0f);
		shader_uniform_16f(c->shader, "modelMatrix", c->ground_trs);
		draw(c->ground);
	}
}
