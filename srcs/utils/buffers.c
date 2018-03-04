/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:57:29 by mploux            #+#    #+#             */
/*   Updated: 2018/03/04 15:51:51 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffers.h"

t_glfloatbuffer		ltfb(t_list *list)
{
	int				size;
	t_list			*start;
	t_glfloatbuffer	result;

	start = list;
	size = 1;
	while ((list = list->next))
		size++;
	result.size = sizeof(GLfloat) * size;
	if (!(result.buffer = (GLfloat *)malloc(result.size)))
		error("Malloc error !");
	list = start;
	size = 0;
	while (list)
	{
		result.buffer[size++] = *((GLfloat *)list->content);
		list = list->next;
	}
	return (result);
}

t_gluintbuffer		ltib(t_list *list)
{
	int				size;
	t_list			*start;
	t_gluintbuffer	result;

	start = list;
	size = 1;
	while ((list = list->next))
		size++;
	result.size = sizeof(GLuint) * size;
	if (!(result.buffer = (GLuint *)malloc(result.size)))
		error("Malloc error !");
	list = start;
	size = 0;
	while (list)
	{
		result.buffer[size++] = *((GLuint *)list->content);
		list = list->next;
	}
	return (result);
}

void				free_ltfb(t_glfloatbuffer *buff)
{
	free(buff->buffer);
	buff->buffer = NULL;
}

void				free_ltib(t_gluintbuffer *buff)
{
	free(buff->buffer);
	buff->buffer = NULL;
}
