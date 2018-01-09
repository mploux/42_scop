/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:27:52 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 19:47:26 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERS_H
# define BUFFERS_H

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

#endif
