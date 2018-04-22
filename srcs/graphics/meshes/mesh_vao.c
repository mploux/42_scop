/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_vao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:50:39 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 17:02:53 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static void	create_vertices(t_mesh *mesh)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size,
										mesh->vertices.buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

static void	create_texcoords(t_mesh *mesh)
{
	if (mesh->texcoords.length > 0)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->tbo);
		glBufferData(GL_ARRAY_BUFFER, mesh->texcoords.size,
										mesh->texcoords.buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	}
}

static void	create_normals(t_mesh *mesh)
{
	if (mesh->normals.length > 0)
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->nbo);
		glBufferData(GL_ARRAY_BUFFER, mesh->normals.size,
										mesh->normals.buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	}
}

static void	create_colors(t_mesh *mesh)
{
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->cbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->colors.size,
										mesh->colors.buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void		create_vao(t_mesh_data *data, t_mesh *mesh)
{
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	if (data->texcoords.length > 0)
		glGenBuffers(1, &mesh->tbo);
	if (data->normals.length > 0)
		glGenBuffers(1, &mesh->nbo);
	glGenBuffers(1, &mesh->cbo);
	glGenBuffers(1, &mesh->ibo);
	glBindVertexArray(mesh->vao);
	create_vertices(mesh);
	create_texcoords(mesh);
	create_normals(mesh);
	create_colors(mesh);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size,
										mesh->indices.buffer, GL_STATIC_DRAW);
	glBindVertexArray(0);
}
