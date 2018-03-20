/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:57:29 by mploux            #+#    #+#             */
/*   Updated: 2018/03/20 17:51:11 by mploux           ###   ########.fr       */
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

void 				buff_push_float(t_glfloatbuffer *buff, GLfloat v)
{
	buff->length++;
	buff->size += sizeof(GLfloat);
	buff->buffer = ft_realloc(buff->buffer, buff->size);
	buff->buffer[buff->length - 1] = v;
}

void 				buff_push_uint(t_gluintbuffer *buff, GLuint v)
{
	buff->length++;
	buff->size += sizeof(GLuint);
	buff->buffer = ft_realloc(buff->buffer, buff->size);
	buff->buffer[buff->length - 1] = v;
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
