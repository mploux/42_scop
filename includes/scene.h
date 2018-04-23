/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:20:15 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 20:35:50 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <libft.h>

# include "entity.h"
# include "shader.h"

typedef struct		s_scene
{
	t_list			*entities;
}					t_scene;

t_scene				init_scene(void);
void				clean_scene(t_scene *s);

void				scene_add(t_scene *s, t_entity *e);

void				scene_update(t_scene *s);
void				scene_render(t_scene *s, t_shader *sh);

#endif
