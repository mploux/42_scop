/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:57:27 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 23:43:18 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_mat4		mat4_ortho(t_vec2 w, t_vec2 h, t_vec2 d)
{
	t_mat4 result;

	result = mat4_identity();
	result.m[0] = 2.0 / (w.y - w.x);
	result.m[5] = -2.0 / (h.x - h.y);
	result.m[10] = -2.0 / (d.y - d.x);
	result.m[3] = -(w.y + w.x) / (w.y - w.x);
	result.m[7] = -(h.x + h.y) / (h.x - h.y);
	result.m[11] = -(d.y + d.x) / (d.y - d.x);
	return (result);
}

t_mat4		mat4_persp(float fov, float aspect, float near, float far)
{
	t_mat4	result;
	float	tfov;

	tfov = tan(DTR(fov) / 2.0);
	result = mat4_identity();
	result.m[0 + 0 * 4] = 1.0 / (aspect * tfov);
	result.m[1 + 1 * 4] = 1.0 / tfov;
	result.m[2 + 2 * 4] = (-far - near) / (near - far);
	result.m[3 + 2 * 4] = (2 * far * near) / (near - far);
	result.m[2 + 3 * 4] = 1;
	result.m[3 + 3 * 4] = 0;
	return (result);
}

t_mat4		mat4_screen_space(float h_width, float h_height)
{
	t_mat4 result;

	result = mat4_identity();
	result.m[0] = h_width;
	result.m[5] = -h_height;
	result.m[3] = h_width;
	result.m[7] = h_height;
	return (result);
}
