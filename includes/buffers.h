/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:27:52 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 21:13:36 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERS_H
# define BUFFERS_H

#include <GL/glew.h>
#include <libft.h>

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

#endif
