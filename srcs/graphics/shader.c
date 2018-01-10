/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:28:48 by mploux            #+#    #+#             */
/*   Updated: 2018/01/10 21:11:02 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

t_shader		*new_shader(const char *vertex_path, const char *fragment_path)
{
	t_shader	*result;
	GLuint		vertex;
	GLuint		fragment;

	if (!(result = (t_shader *)malloc(sizeof(t_shader))))
		error("Malloc error !");
	if ((result->program = glCreateProgram()) == GL_FALSE)
		error("Unable to create shader program");
	vertex = create_shader(load_file(vertex_path), GL_VERTEX_SHADER);
	fragment = create_shader(load_file(fragment_path), GL_FRAGMENT_SHADER);
	glAttachShader(result->program, vertex);
	glAttachShader(result->program, fragment);
	glLinkProgram(result->program);
	glValidateProgram(result->program);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return (result);
}

GLuint			create_shader(const char *source, int type)
{
	GLuint		shader;
	GLint		result;
	GLchar		*err;
	GLint		length;

	shader = glCreateShader(type);
	if (shader == GL_FALSE)
		error("Unable to create the shader !");
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		err = ft_strnew(length);
		glGetShaderInfoLog(shader, length, &length, err);
		ft_putstr(err);
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}

void 			delete_shader(t_shader *shader)
{
	
}
