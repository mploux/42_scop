/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:03:07 by mploux            #+#    #+#             */
/*   Updated: 2018/03/25 13:09:44 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_core		init_core(int av, char **ac)
{
	t_core	c;

	c.display = init_display("scop - 42 - mploux", 1280, 720);
	c.input = init_input(c.display.window);
	c.shader = new_shader("data/shaders/main.vert", "data/shaders/main.frag");
	c.texture = new_texture(ac[2]);
	c.model = new_model(ac[1]);
	c.model_pos = vec3(0, 0, 5);
	c.model_rot = vec3(0.0f, 270.0f, 0.0f);
	c.model_scale = vec3(1, 1, 1);
	return (c);
}

void 		clean_core(t_core *core)
{
	delete_shader(&core->shader);
	delete_mesh(&core->model);
	delete_texture(&core->texture);
	clean_display(&core->display);
}

void		run_core(t_core *core)
{
	while (!glfwWindowShouldClose(core->display.window))
	{
		input_update(&core->input);
		if (get_key_down(&core->input, GLFW_KEY_ESCAPE) && !core->input.focused)
			break;
		input_handle_focus(&core->input);
		if (get_key_up(&core->input, GLFW_KEY_1))
			core->use_texture = 1.0f - core->use_texture;
		if (get_key_up(&core->input, GLFW_KEY_2) && core->model->texcoords.length > 0)
			core->use_texcoord = 1.0f - core->use_texcoord;
		if (get_key_up(&core->input, GLFW_KEY_3) && core->model->normals.length > 0)
			core->use_normal = 1.0f - core->use_normal;
		update(core);
		render(core);
		usleep(1000000 / 60);
	}
}

void		update(t_core *core)
{
	core->model_rot.y++;
	core->model_trs = mat4_transform(core->model_pos, core->model_rot, core->model_scale);
	core->model_centered_trs = mat4_translate(vec3_negate(core->model->center));
}

void		render(t_core *core)
{
	t_mat4	transformation;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(core->shader->program);
	glUniformMatrix4fv(glGetUniformLocation(core->shader->program, "projectionMatrix"), 1, GL_FALSE, mat4_persp(70.0f, 1280.0f / 720.0f, 0.1f, 100.0f).m);
	glUniform1f(glGetUniformLocation(core->shader->program, "use_texcoord"), core->use_texcoord);
	glUniform1f(glGetUniformLocation(core->shader->program, "use_texture"), core->use_texture);
	glUniform1f(glGetUniformLocation(core->shader->program, "use_normal"), core->use_normal);
	transformation = mat4_mul(core->model_trs, core->model_centered_trs);
	bind_texture(core->texture);
	transform(&transformation, core->shader);
	draw(core->model);
	glfwSwapBuffers(core->display.window);
	glfwPollEvents();
}
