/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:36:25 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 16:44:13 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void	convert_vertices(t_mesh_data *m, t_model_data *d, t_model_index *i,
																		int j)
{
	int index[3];

	index[0] = i[j].position * 3 + 0;
	index[1] = i[j].position * 3 + 1;
	index[2] = i[j].position * 3 + 2;
	m->vertices.buffer[j * 3 + 0] = d->positions.buffer[index[0]];
	m->vertices.buffer[j * 3 + 1] = d->positions.buffer[index[1]];
	m->vertices.buffer[j * 3 + 2] = d->positions.buffer[index[2]];
}

static void	convert_coords(t_mesh_data *m, t_model_data *d, t_model_index *i,
																		int j)
{
	int index[2];

	if (d->texcoords_i.buffer != NULL && d->texcoords.buffer != NULL)
	{
		index[0] = i[j].texture * 2 + 0;
		index[1] = i[j].texture * 2 + 1;
		m->texcoords.buffer[j * 2 + 0] = d->texcoords.buffer[index[0]];
		m->texcoords.buffer[j * 2 + 1] = d->texcoords.buffer[index[1]];
	}
}

static void	convert_normals(t_mesh_data *m, t_model_data *d, t_model_index *i,
																		int j)
{
	int index[3];

	if (d->normals_i.buffer != NULL && d->normals.buffer != NULL)
	{
		index[0] = i[j].normal * 3 + 0;
		index[1] = i[j].normal * 3 + 1;
		index[2] = i[j].normal * 3 + 2;
		m->normals.buffer[j * 3 + 0] = d->normals.buffer[index[0]];
		m->normals.buffer[j * 3 + 1] = d->normals.buffer[index[1]];
		m->normals.buffer[j * 3 + 2] = d->normals.buffer[index[2]];
	}
}

t_mesh		*convert_to_mesh(t_model_data *data, t_model_index *i, int size)
{
	int				j;
	t_mesh_data		mesh_data;

	j = -1;
	mesh_data.vertices = init_vertices(&data->positions, size);
	mesh_data.texcoords = init_texcoords(&data->texcoords, size);
	mesh_data.normals = init_normals(&data->normals, size);
	mesh_data.indices = init_indices(i, size);
	mesh_data.dimension.x = data->max_vertices.x - data->min_vertices.x;
	mesh_data.dimension.y = data->max_vertices.y - data->min_vertices.y;
	mesh_data.dimension.z = data->max_vertices.z - data->min_vertices.z;
	mesh_data.center.x = data->max_vertices.x - mesh_data.dimension.x / 2.0f;
	mesh_data.center.y = data->max_vertices.y - mesh_data.dimension.y / 2.0f;
	mesh_data.center.z = data->max_vertices.z - mesh_data.dimension.z / 2.0f;
	while (++j < size)
	{
		convert_vertices(&mesh_data, data, i, j);
		convert_coords(&mesh_data, data, i, j);
		convert_normals(&mesh_data, data, i, j);
		mesh_data.indices.buffer[j] = j;
	}
	return (new_mesh(&mesh_data));
}
