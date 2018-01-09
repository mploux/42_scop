/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:57:29 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 21:14:46 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffers.h"

t_glfloatbuffer		ltfb(t_list *list)
{
	int				size;
	t_list			*start;
	t_glfloatbuffer	result;

	start = list;
	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	result.size = sizeof(GLfloat) * size;
	if (!(result.buffer = (GLfloat *)malloc(result.size)))
		error("Malloc error !");
	list = start;
	size = 0;
	while (list)
	{
		result.buffer[size] = *((GLfloat *)list->content);
		list = list->next;
		size++;
	}
}

t_gluintbuffer		ltib(t_list *list)
{
	int				size;
	t_list			*start;
	t_gluintbuffer	result;

	start = list;
	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	result.size = sizeof(GLuint) * size;
	if (!(result.buffer = (GLuint *)malloc(result.size)))
		error("Malloc error !");
	list = start;
	size = 0;
	while (list)
	{
		result.buffer[size] = *((GLuint *)list->content);
		list = list->next;
		size++;
	}
}
