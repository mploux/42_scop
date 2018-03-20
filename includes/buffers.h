/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:27:52 by mploux            #+#    #+#             */
/*   Updated: 2018/03/20 17:43:18 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERS_H
# define BUFFERS_H

# include <GL/glew.h>
# include <libft.h>
# include "error.h"

typedef struct		s_glfloatbuffer
{
	int				length;
	int				size;
	GLfloat			*buffer;
}					t_glfloatbuffer;

typedef struct		s_gluintbuffer
{
	int				length;
	int				size;
	GLuint			*buffer;
}					t_gluintbuffer;

t_glfloatbuffer		ltfb(t_list *list);
t_gluintbuffer		ltib(t_list *list);
void 				buff_push_float(t_glfloatbuffer *buff, GLfloat v);
void 				buff_push_uint(t_gluintbuffer *buff, GLuint v);

void				free_ltfb(t_glfloatbuffer *buff);
void				free_ltib(t_gluintbuffer *buff);

#endif
