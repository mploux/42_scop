/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:22:31 by mploux            #+#    #+#             */
/*   Updated: 2018/01/10 21:49:45 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh			*new_mesh(t_glfloatbuffer *v, t_gluintbuffer *i)
{
	t_mesh	*result;

	if (!(result = (t_mesh *)malloc(sizeof(t_mesh))))
		error("Malloc error !");
	result->vertices = *v;
	result->indices = *i;
	glGenVertexArrays(1, &result->vao);
	glGenBuffers(1, &result->vbo);
	glGenBuffers(1, &result->ibo);
	glBindVertexArray(result->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, result->vbo);
	glBufferData(GL_ARRAY_BUFFER, v->size, v->buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i->size, i->buffer, GL_STATIC_DRAW);
	glBindVertexArray(0);

	return (result);
}

void			delete_mesh(t_mesh **mesh)
{
	free(*mesh);
}

void			draw(t_mesh *mesh)
{
	int drawSize;

	drawSize = mesh->indices.size / sizeof(GLuint);
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, drawSize, GL_UNSIGNED_INT, 0L);
	glBindVertexArray(0);
}
