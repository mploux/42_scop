/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:25:18 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 18:18:24 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controls.h"

void	handle_controls(t_core *c, float speed)
{
	if (get_key(&c->input, GLFW_KEY_UP))
		c->model_pos.z += speed;
	if (get_key(&c->input, GLFW_KEY_DOWN))
		c->model_pos.z -= speed;
	if (get_key(&c->input, GLFW_KEY_LEFT))
		c->model_pos.x -= speed;
	if (get_key(&c->input, GLFW_KEY_RIGHT))
		c->model_pos.x += speed;
	if (get_key(&c->input, GLFW_KEY_KP_1))
		c->model_pos.y -= speed;
	if (get_key(&c->input, GLFW_KEY_KP_4))
		c->model_pos.y += speed;
	if (get_key(&c->input, GLFW_KEY_R))
		c->model_pos = vec3(0, 0, 0);
}

void	handle_render_controls(t_core *c, float speed)
{
	(void) speed;
	if (get_key_up(&c->input, GLFW_KEY_1))
		c->use_texture = 1 - c->use_texture;
	if (get_key_up(&c->input, GLFW_KEY_2) && c->model->texcoords.length > 0)
		c->use_texcoord = 1 - c->use_texcoord;
	if (get_key_up(&c->input, GLFW_KEY_4) && c->model->normals.length > 0)
		c->use_normal = 1 - c->use_normal;
	if (c->use_texture)
		c->use_texture_f += speed;
	else
		c->use_texture_f -= speed;
	if (c->use_texcoord)
		c->use_texcoord_f += speed;
	else
		c->use_texcoord_f -= speed;
	if (c->use_normal)
		c->use_normal_f += speed;
	else
		c->use_normal_f -= speed;
	c->use_texture_f = clamp(c->use_texture_f, 0.0f, 1.0f);
	c->use_texcoord_f = clamp(c->use_texcoord_f, 0.0f, 1.0f);
	c->use_normal_f = clamp(c->use_normal_f, 0.0f, 1.0f);
}

void	handle_mouse_controls(t_core *c, float speed)
{
	c->camera.rotation.x -= c->input.mouse_velocity.y * speed;
	c->camera.rotation.y -= c->input.mouse_velocity.x * speed;
	if (c->camera.rotation.x < -90)
		c->camera.rotation.x = -90;
	if (c->camera.rotation.x > 90)
		c->camera.rotation.x = 90;
}

void	handle_camera_controls(t_core *c, float speed)
{
	t_vec3	m;
	float	yrot;

	m = vec3(0, 0, 0);
	yrot = DTR(c->camera.rotation.y);
	if (get_key(&c->input, GLFW_KEY_W))
		m.z += speed;
	if (get_key(&c->input, GLFW_KEY_S))
		m.z -= speed;
	if (get_key(&c->input, GLFW_KEY_A))
		m.x -= speed;
	if (get_key(&c->input, GLFW_KEY_D))
		m.x += speed;
	if (get_key(&c->input, GLFW_KEY_SPACE))
		m.y += speed;
	if (get_key(&c->input, GLFW_KEY_LEFT_SHIFT))
		m.y -= speed;
	c->camera.position.x += m.x * cos(yrot) - m.z * sin(yrot);
	c->camera.position.y += m.y;
	c->camera.position.z += m.z * cos(yrot) + m.x * sin(yrot);
}


void	handle_rotation_controls(t_core *c, float speed)
{
	if (get_key(&c->input, GLFW_KEY_J))
		c->rot_factor.y += speed;
	if (get_key(&c->input, GLFW_KEY_L))
		c->rot_factor.y -= speed;
	if (get_key(&c->input, GLFW_KEY_I))
		c->rot_factor.z -= speed;
	if (get_key(&c->input, GLFW_KEY_K))
		c->rot_factor.z += speed;
	if (get_key(&c->input, GLFW_KEY_U))
		c->rot_factor.x -= speed;
	if (get_key(&c->input, GLFW_KEY_O))
		c->rot_factor.x += speed;
	if (get_key(&c->input, GLFW_KEY_R))
	{
		c->rot_factor = vec3(0, 1, 0);
		c->model_rot = vec3(0, 0, 0);
	}
}
