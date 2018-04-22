/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:36:25 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 18:23:10 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void	convert_vertices(t_mesh_data *m, t_model_data *d, t_model_index *i,
																		int j)
{
	int k;
	int index[3];

	k = -1;
	if (d->positions_i.buffer != NULL && d->positions.buffer != NULL)
	{
		while (++k < 3)
		{
			index[k] = i[j].position * 3 + k;
			if (index[k] >= 0 && (size_t)index[k] < d->positions.length)
			m->vertices.buffer[j * 3 + k] = d->positions.buffer[index[k]];
		}
	}
}

static void	convert_coords(t_mesh_data *m, t_model_data *d, t_model_index *i,
																		int j)
{
	int k;
	int index[2];

	k = -1;
	if (d->texcoords_i.buffer != NULL && d->texcoords.buffer != NULL)
	{
		while (++k < 2)
		{
			index[k] = i[j].texture * 2 + k;
			if (index[k] >= 0 && (size_t)index[k] < d->texcoords.length)
				m->texcoords.buffer[j * 2 + k] = d->texcoords.buffer[index[k]];
		}
	}
}

static void	convert_normals(t_mesh_data *m, t_model_data *d, t_model_index *i,
																		int j)
{
	int k;
	int index[3];

	k = -1;
	if (d->normals_i.buffer != NULL && d->normals.buffer != NULL)
	{
		while (++k < 3)
		{
			index[k] = i[j].normal * 3 + k;
			if (index[k] >= 0 && (size_t)index[k] < d->normals.length)
				m->normals.buffer[j * 3 + k] = d->normals.buffer[index[k]];
		}
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
	mesh_data.max_dim = max_val(mesh_data.dimension.x,
						max_val(mesh_data.dimension.y, mesh_data.dimension.z));
	while (++j < size)
	{
		convert_vertices(&mesh_data, data, i, j);
		convert_coords(&mesh_data, data, i, j);
		convert_normals(&mesh_data, data, i, j);
		mesh_data.indices.buffer[j] = j;
	}
	return (new_mesh(&mesh_data));
}
