/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:24:55 by mploux            #+#    #+#             */
/*   Updated: 2018/01/07 18:24:14 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

#include <libft.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "error.h"

typedef struct	s_shader
{
	GLuint		program;
}				t_shader;

t_shader		*new_shader(const char *vertex_path, const char *fragment_path);
GLuint			createShader(const char *source, int type);

#endif
