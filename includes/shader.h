/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:24:55 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 01:10:49 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

#include <libft.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "error.h"
#include "maths.h"

typedef struct	s_shader
{
	GLuint		program;
}				t_shader;

t_shader		*new_shader(const char *vertex_path, const char *fragment_path);
void			delete_shader(t_shader **shader);
GLuint			create_shader(const char *source, int type);

void			shader_uniform_1f(t_shader *shader, const char *n, float val);
void			shader_uniform_1i(t_shader *shader, const char *n, int val);
void			shader_uniform_3f(t_shader *shader, const char *n, t_vec3 val);
void			shader_uniform_16f(t_shader *shader, const char *n, t_mat4 val);

#endif
