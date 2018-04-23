/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 01:28:06 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 18:38:16 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"

t_entity	*new_entity(t_mesh *mesh, t_camera *c)
{
	t_entity	*result;

	if (!(result = (t_entity *)malloc(sizeof(t_entity))))
		error("Malloc error !");
	result->mesh = mesh;
	result->pos = c->position;
	result->rot = c->rotation;
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
	t_mat4 ctr;
	t_mat4 rotx;
	t_mat4 roty;
	t_mat4 final_trs;


	rotx = mat4_rotate(vec3(1, 0, 0), -e->rot.x);
	roty = mat4_rotate(vec3(0, 1, 0), -e->rot.y);
	trs = mat4_mul(mat4_translate(e->pos), mat4_mul(roty, rotx));
	ctr = mat4_translate(vec3_negate(e->mesh->center));
	final_trs = mat4_mul(trs, ctr);
	transform(&final_trs, s);
	draw(e->mesh);
}
