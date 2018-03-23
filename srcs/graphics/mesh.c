/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:22:31 by mploux            #+#    #+#             */
/*   Updated: 2018/03/23 10:49:12 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh			*new_mesh(t_glfloatbuffer *v, t_glfloatbuffer *t, t_glfloatbuffer *n, t_gluintbuffer *i)
{
	t_mesh	*result;

	if (!(result = (t_mesh *)malloc(sizeof(t_mesh))))
		error("Malloc error !");

	result->vertices = *v;
	result->texcoords = *t;
	result->normals = *n;
	result->colors = generate_colors(v);
	result->indices = *i;

	glGenVertexArrays(1, &result->vao);

	glGenBuffers(1, &result->vbo);
	if (t->length > 0)
		glGenBuffers(1, &result->tbo);
	if (n->length > 0)
		glGenBuffers(1, &result->nbo);
	glGenBuffers(1, &result->cbo);
	glGenBuffers(1, &result->ibo);

	glBindVertexArray(result->vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, result->vbo);
		glBufferData(GL_ARRAY_BUFFER, v->size, v->buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		if (t->length > 0)
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, result->tbo);
			glBufferData(GL_ARRAY_BUFFER, t->size, t->buffer, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
		}
		if (n->length > 0)
		{
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, result->nbo);
			glBufferData(GL_ARRAY_BUFFER, n->size, n->buffer, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		}

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, result->cbo);
		glBufferData(GL_ARRAY_BUFFER, result->colors.size, result->colors.buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, i->size, i->buffer, GL_STATIC_DRAW);

	glBindVertexArray(0);

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
	free((*mesh)->indices.buffer);
	free(*mesh);
	*mesh = NULL;
}

t_glfloatbuffer	generate_colors(t_glfloatbuffer *v)
{
	size_t			i;
	int				j;
	t_glfloatbuffer	result;

	i = -1;
	result.length = v->size / sizeof(GLfloat);
	result.size = sizeof(t_glfloatbuffer) * (result.length);
	result.buffer = (GLfloat *)malloc(result.size);
	if (!result.buffer)
		error("Malloc error !");
	int size = 9;
	while (++i < result.length / size)
	{
		j = -1;
		while (++j < size)
			result.buffer[i * size + j] = (GLfloat)(i % 9) / 9.0;
	}
	return (result);
}

void			draw(t_mesh *mesh)
{
	int draw_size;

	draw_size = mesh->indices.size / sizeof(GLuint);
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, draw_size, GL_UNSIGNED_INT, 0L);
	glBindVertexArray(0);
}
