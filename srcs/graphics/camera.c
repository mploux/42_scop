/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 21:46:59 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 16:40:23 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera	init_camera(t_display *disp, float fov, float near, float far)
{
	t_camera result;

	result.display = disp;
	camera_proj(&result, fov, near, far);
	result.position = vec3(0, 0, -5);
	result.rotation = vec2(0, 0);
	return (result);
}

void		camera_proj(t_camera *cam, float fov, float near, float far)
{
	cam->fov = fov;
	cam->aspect = (float)cam->display->width / (float)cam->display->height;
	cam->near = near;
	cam->far = far;
	cam->projection = mat4_persp(cam->fov, cam->aspect, cam->near, cam->far);
}

void		resize(t_display *disp, t_camera *cam)
{
	int w;
	int h;

	w = 0;
	h = 0;
	glfwGetWindowSize(disp->window, &w, &h);
	if (w != disp->width || h != disp->height)
	{
		disp->width = w;
		disp->height = h;
		glViewport(0, 0, disp->width, disp->height);
		camera_proj(cam, cam->fov, cam->near, cam->far);
	}
}

void		camera_update(t_camera *cam)
{
	t_mat4	translation;
	t_mat4	rotation_x;
	t_mat4	rotation_y;
	t_mat4	rotation;

	translation = mat4_translate(vec3_negate(cam->position));
	rotation_x = mat4_rotate(vec3(1, 0, 0), cam->rotation.x);
	rotation_y = mat4_rotate(vec3(0, 1, 0), cam->rotation.y);
	rotation = mat4_mul(rotation_x, rotation_y);
	cam->transform = mat4_mul(rotation, translation);
}
