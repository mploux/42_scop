/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 01:21:41 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 02:07:01 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "mesh.h"
# include "maths.h"

typedef struct	s_entity
{
	t_mesh		*mesh;
	t_vec3		pos;
	t_vec2		rot;
	t_vec3		scale;
	t_mat4		transform;
	t_mat4		center;
	t_vec3		rot_factor;
}				t_entity;

t_entity		*new_entity(t_mesh *m, t_vec3 pos, t_vec2 rot, t_vec3 scale);
void			delete_entity(t_entity **e);

void			entity_update(t_entity	*e);
void			entity_render(t_entity	*e, t_shader *s);

#endif
