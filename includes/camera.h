/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 21:34:30 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 20:35:44 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "maths.h"
# include "display.h"

typedef struct	s_camera
{
	t_display	*display;
	float		fov;
	float		aspect;
	float		near;
	float		far;
	t_vec3		position;
	t_vec2		rotation;
	t_mat4		transform;
	t_mat4		projection;
}				t_camera;

t_camera		init_camera(t_display *disp, float fov, float near, float far);
void			camera_proj(t_camera *cam, float fov, float near, float far);
void			camera_update(t_camera *cam);
void			resize(t_display *disp, t_camera *cam);

#endif
