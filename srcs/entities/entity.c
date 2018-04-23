/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 01:28:06 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 16:40:53 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"

t_entity	*new_entity(t_mesh *mesh, t_vec3 pos, t_vec2 rot)
{
	t_entity	*result;

	if (!(result = (t_entity *)malloc(sizeof(t_entity))))
		error("Malloc error !");
	result->mesh = mesh;
	result->pos = pos;
	result->rot = vec2(rot.x, rot.y);
	result->scale = vec3(1, 1, 1);
	return (result);
}

void		delete_entity(t_entity **e)
{
	if (e && *e)
		free(*e);
}

void		entity_update(t_entity	*e)
{
	(void)e;
}

void		entity_render(t_entity	*e, t_shader *s)
{
	t_mat4 trs;
	t_mat4 rot;

	rot = mat4_rotate_xyz(e->rot.x, e->rot.y, 0);
	trs = mat4_translate(e->pos);
	transform(&trs, s);
	draw(e->mesh);
}
