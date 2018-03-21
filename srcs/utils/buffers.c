/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:57:29 by mploux            #+#    #+#             */
/*   Updated: 2018/03/21 13:44:53 by mploux           ###   ########.fr       */
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
	GLfloat	*new;

	buff->length++;
	if (sizeof(GLfloat) * (buff->length) > buff->size || buff->buffer == NULL)
	{
		new = (GLfloat *)malloc(buff->size + sizeof(GLfloat) * MAX_BUFF_SIZE);
		if (!new)
			error("Float push failed !");
		ft_memcpy(new, buff->buffer, buff->size);
		free(buff->buffer);
		buff->buffer = new;
		buff->size += sizeof(GLfloat) * MAX_BUFF_SIZE;
	}
	buff->buffer[buff->length - 1] = v;
}

void 				buff_push_uint(t_gluintbuffer *buff, GLuint v)
{
	GLuint	*new;

	buff->length++;
	if (sizeof(GLuint) * (buff->length) > buff->size || buff->buffer == NULL)
	{
		new = (GLuint *)malloc(buff->size + sizeof(GLuint) * MAX_BUFF_SIZE);
		if (!new)
			error("Float push failed !");
		ft_memcpy(new, buff->buffer, buff->size);
		free(buff->buffer);
		buff->buffer = new;
		buff->size += sizeof(GLuint) * MAX_BUFF_SIZE;
	}
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
