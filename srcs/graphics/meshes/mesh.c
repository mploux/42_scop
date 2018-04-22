/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:22:31 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 16:56:10 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh			*new_mesh(t_mesh_data *data)
{
	t_mesh	*result;

	if (!(result = (t_mesh *)malloc(sizeof(t_mesh))))
		error("Malloc error !");
	result->vertices = data->vertices;
	result->texcoords = data->texcoords;
	result->normals = data->normals;
	result->colors = generate_colors(&data->vertices);
	result->indices = data->indices;
	result->dimension = data->dimension;
	result->center = data->center;
	create_vao(data, result);
	return (result);
}

void			delete_mesh(t_mesh **mesh)
{
	glDeleteVertexArrays(1, &(*mesh)->vao);
	glDeleteBuffers(1, &(*mesh)->vbo);
	glDeleteBuffers(1, &(*mesh)->tbo);
	glDeleteBuffers(1, &(*mesh)->nbo);
	glDeleteBuffers(1, &(*mesh)->ibo);
	free((*mesh)->vertices.buffer);
	free((*mesh)->texcoords.buffer);
	free((*mesh)->normals.buffer);
	free((*mesh)->colors.buffer);
	free((*mesh)->indices.buffer);
	free(*mesh);
	*mesh = NULL;
}

t_glfloatbuffer	generate_colors(t_glfloatbuffer *v)
{
	size_t			i;
	int				j;
	t_glfloatbuffer	result;
	int				size;

	i = -1;
	result.length = v->size / sizeof(GLfloat);
	result.size = sizeof(t_glfloatbuffer) * (result.length);
	result.buffer = (GLfloat *)malloc(result.size);
	if (!result.buffer)
		error("Malloc error !");
	size = 9;
	while (++i < result.length / size)
	{
		j = -1;
		while (++j < size)
			result.buffer[i * size + j] = (GLfloat)(i % 9) / 9.0;
	}
	return (result);
}

void			transform(t_mat4 *transform, t_shader *shader)
{
	GLuint	location;

	location = glGetUniformLocation(shader->program, "viewMatrix");
	glUniformMatrix4fv(location, 1, GL_TRUE, transform->m);
}

void			draw(t_mesh *mesh)
{
	int draw_size;

	draw_size = mesh->indices.size / sizeof(GLuint);
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, draw_size, GL_UNSIGNED_INT, 0L);
	glBindVertexArray(0);
}
