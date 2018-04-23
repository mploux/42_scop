/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:03:07 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 02:17:38 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_core		init_core(int av, char **ac)
{
	t_core	c;
	float	scale;

	c.display = init_display("scop - 42 - mploux", 1280, 720);
	c.input = init_input(c.display.window);
	c.camera = init_camera(&c.display, 70.0f, 0.5f, 100.0f);
	c.shader = new_shader("data/shaders/main.vert", "data/shaders/main.frag");
	c.texture = new_texture(ac[2]);
	c.model = new_model(ac[1]);
	c.ground = new_model("data/models/plane.obj");
	c.entities = NULL;
	c.show_ground = 0;
	c.model_pos = vec3(0, 0, 0);
	c.model_rot = vec3(0.0f, 270.0f, 0.0f);
	scale = 3.0f / c.model->max_dim;
	c.model_scale = vec3(scale, scale, scale);
	c.rot_factor = vec3(0, 1, 0);
	c.use_normal = 0;
	c.use_texture = 0;
	c.use_texcoord = 0;
	c.light_pos = c.camera.position;
	return (c);
}

void		clean_core(t_core *core)
{
	delete_shader(&core->shader);
	delete_mesh(&core->model);
	delete_texture(&core->texture);
	clean_display(&core->display);
}

void		run_core(t_core *c)
{
	clock_t	before_time;
	clock_t	current_time;

	before_time = clock();
	while (!glfwWindowShouldClose(c->display.window))
	{
		current_time = clock();
		if (current_time - before_time > 1000000.0 / 60.0)
		{
			input_update(&c->input);
			if (get_key_down(&c->input, GLFW_KEY_ESCAPE) && !c->input.focused)
				break ;
			input_handle_focus(&c->input);
			update(c);
			before_time = clock();
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(c);
		glfwSwapBuffers(c->display.window);
		glfwPollEvents();
	}
}

void		update(t_core *c)
{
	camera_update(&c->camera);
	if (get_key_up(&c->input, GLFW_KEY_1))
		c->use_texture = 1.0f - c->use_texture;
	if (get_key_up(&c->input, GLFW_KEY_2) && c->model->texcoords.length > 0)
		c->use_texcoord = 1.0f - c->use_texcoord;
	if (get_key_up(&c->input, GLFW_KEY_3))
		c->show_ground = !c->show_ground;
	if (get_key_up(&c->input, GLFW_KEY_4) && c->model->normals.length > 0)
		c->use_normal = 1.0f - c->use_normal;
	if (get_key_up(&c->input, GLFW_KEY_5))
		c->light_pos = c->camera.position;
	if (get_key_up(&c->input, GLFW_KEY_Q))
		ft_lstadd(&c->entities, ft_lstnew(new_entity(c->model, c->camera.position, c->camera.rotation, vec3(1, 1, 1)), sizeof(t_entity)));
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
	t_list	*list;

	glUseProgram(c->shader->program);
	shader_uniform_16f(c->shader, "projectionMatrix", c->camera.projection);
	shader_uniform_16f(c->shader, "viewMatrix", c->camera.transform);
	shader_uniform_1f(c->shader, "use_texcoord", c->use_texcoord);
	shader_uniform_1f(c->shader, "use_texture", c->use_texture);
	shader_uniform_1f(c->shader, "use_normal", c->use_normal);
	shader_uniform_3f(c->shader, "light_pos", c->light_pos);
	transformation = mat4_mul(c->model_trs, c->model_centered_trs);
	bind_texture(c->texture);
	transform(&transformation, c->shader);
	draw(c->model);
	if (c->show_ground)
	{
		shader_uniform_1f(c->shader, "use_texcoord", 1.0f);
		shader_uniform_1f(c->shader, "use_texture", 1.0f);
		shader_uniform_16f(c->shader, "modelMatrix", mat4_translate(vec3(0, -2, 0)));
		draw(c->ground);
	}
	list = c->entities;
	while (list)
	{
		t_entity *e = (t_entity *)list->content;
		entity_render(e, c->shader);
		list = list->next;
	}
}
