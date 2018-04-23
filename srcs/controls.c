/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:25:18 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 01:17:43 by mploux           ###   ########.fr       */
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
		c->model_pos = vec3(0, 0, 5);
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
