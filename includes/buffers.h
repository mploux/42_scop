/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:27:52 by mploux            #+#    #+#             */
/*   Updated: 2018/01/11 21:03:28 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERS_H
# define BUFFERS_H

#include <GL/glew.h>
#include <libft.h>
#include "error.h"

typedef struct		s_glfloatbuffer
{
	int				size;
	GLfloat			*buffer;
}					t_glfloatbuffer;

typedef struct		s_gluintbuffer
{
	int				size;
	GLuint			*buffer;
}					t_gluintbuffer;

t_glfloatbuffer		ltfb(t_list *list);
t_gluintbuffer		ltib(t_list *list);

t_gluintbuffer		*new_gluint_buff(int size);
t_gluintbuffer		*new_glfloat_buff(int size);

void				free_ltfb(t_glfloatbuffer *buff);
void				free_ltib(t_gluintbuffer *buff);

#endif
