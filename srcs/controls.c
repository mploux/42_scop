/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:25:18 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 18:44:41 by mploux           ###   ########.fr       */
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

void	handle_rotation_controls(t_core *c, float speed)
{
	if (get_key(&c->input, GLFW_KEY_J))
		c->rot_factor.y -= speed;
	if (get_key(&c->input, GLFW_KEY_L))
		c->rot_factor.y += speed;
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
