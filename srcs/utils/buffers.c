/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:57:29 by mploux            #+#    #+#             */
/*   Updated: 2018/03/23 00:34:09 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffers.h"

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
