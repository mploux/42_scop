/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:20:00 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 20:35:21 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene		init_scene(void)
{
	t_scene result;

	result.entities = NULL;
	return (result);
}

void		clean_scene(t_scene *s)
{
	ft_lstclear(&s->entities);
	s->entities = NULL;
}

void		scene_add(t_scene *s, t_entity *e)
{
	t_list *new;

	new = ft_lstnew(e, sizeof(t_entity));
	ft_lstadd(&s->entities, new);
}

void		scene_update(t_scene *s)
{
	t_list		*list;
	t_entity	*e;

	list = s->entities;
	while (list)
	{
		e = (t_entity *)list->content;
		entity_update(e);
		list = list->next;
	}
}

void		scene_render(t_scene *s, t_shader *sh)
{
	t_list		*list;
	t_entity	*e;

	list = s->entities;
	while (list)
	{
		e = (t_entity *)list->content;
		entity_render(e, sh);
		list = list->next;
	}
}
