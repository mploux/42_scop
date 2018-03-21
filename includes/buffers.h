/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:27:52 by mploux            #+#    #+#             */
/*   Updated: 2018/03/21 14:05:50 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERS_H
# define BUFFERS_H

# include <GL/glew.h>
# include <libft.h>
# include "error.h"

# define MAX_BUFF_SIZE (size_t)(4096)

typedef struct		s_glfloatbuffer
{
	size_t			length;
	size_t			size;
	GLfloat			*buffer;
}					t_glfloatbuffer;

typedef struct		s_gluintbuffer
{
	size_t			length;
	size_t			size;
	GLuint			*buffer;
}					t_gluintbuffer;

t_glfloatbuffer		ltfb(t_list *list);
t_gluintbuffer		ltib(t_list *list);
void 				buff_push_float(t_glfloatbuffer *buff, GLfloat v);
void 				buff_push_uint(t_gluintbuffer *buff, GLuint v);

void				free_ltfb(t_glfloatbuffer *buff);
void				free_ltib(t_gluintbuffer *buff);

#endif
