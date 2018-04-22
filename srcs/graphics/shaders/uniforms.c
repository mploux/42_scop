/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniforms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 01:01:22 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 01:59:24 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

void	shader_uniform_1f(t_shader *shader, const char *name, float val)
{
	GLint location;

	location = glGetUniformLocation(shader->program, name);
	glUniform1f(location, val);
}

void	shader_uniform_1i(t_shader *shader, const char *name, int val)
{
	GLint location;

	location = glGetUniformLocation(shader->program, name);
	glUniform1i(location, val);
}

void	shader_uniform_3f(t_shader *shader, const char *name, t_vec3 val)
{
	GLint location;

	location = glGetUniformLocation(shader->program, name);
	glUniform3f(location, val.x, val.y, val.z);
}

void	shader_uniform_16f(t_shader *shader, const char *name, t_mat4 val)
{
	GLint location;

	location = glGetUniformLocation(shader->program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, val.m);
}
