/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/03/23 23:30:49 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void		parse_vertices(t_model_data *data, char **tokens)
{
	t_vec3	v;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		error("Model parser error: Invalid vertices !");
	v.x = atof(tokens[1]);
	v.y = atof(tokens[2]);
	v.z = atof(tokens[3]);
	buff_push_float(&data->positions, v.x);
	buff_push_float(&data->positions, v.y);
	buff_push_float(&data->positions, v.z);
	if (v.x < data->min_vertices.x)
		data->min_vertices.x = v.x;
	if (v.y < data->min_vertices.y)
		data->min_vertices.y = v.y;
	if (v.z < data->min_vertices.z)
		data->min_vertices.z = v.z;
	if (v.x > data->max_vertices.x)
		data->max_vertices.x = v.x;
	if (v.y > data->max_vertices.y)
		data->max_vertices.y = v.y;
	if (v.z > data->max_vertices.z)
		data->max_vertices.z = v.z;
}

static void		parse_normals(t_model_data *data, char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		error("Model parser error: Invalid normals !");
	buff_push_float(&data->normals, atof(tokens[1]));
	buff_push_float(&data->normals, atof(tokens[2]));
	buff_push_float(&data->normals, atof(tokens[3]));
}

static void		parse_texcoords(t_model_data *data, char **tokens)
{
	if (!tokens[1] || !tokens[2])
		error("Model parser error: Invalid texcoords !");
	buff_push_float(&data->texcoords, atof(tokens[1]));
	buff_push_float(&data->texcoords, atof(tokens[2]));
}

static int		get_index_count(char *index)
{
	int		result;
	int		i;

	i = -1;
	result = 0;
	while (index[++i])
		if (index[i] == '/')
			result++;
	result++;
	return (result);
}

static void		push_quad_index_data(t_gluintbuffer *buff, char ***toks, int i)
{
	buff_push_uint(buff, ft_atoi(toks[0][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[1][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[2][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[0][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[2][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[3][i]) - 1);
}

static void		push_tri_index_data(t_gluintbuffer *buff, char ***toks, int i)
{
	buff_push_uint(buff, ft_atoi(toks[0][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[1][i]) - 1);
	buff_push_uint(buff, ft_atoi(toks[2][i]) - 1);
}

static void		parse_indces(t_model_data *data, char **tokens)
{
	char		**toks[4];
	int			index_count[4];

	if (tokens[1] && tokens[2] && tokens[3] && !tokens[4])
	{
		index_count[0] = get_index_count(tokens[1]);
		index_count[1] = get_index_count(tokens[2]);
		index_count[2] = get_index_count(tokens[3]);

		if (index_count[0] != index_count[1] ||
			index_count[1] != index_count[2] ||
			index_count[0] != index_count[2])
			error("Model parser error: Unconsistent indices !");
		if (index_count[0] == 1)
		{
			buff_push_uint(&data->positions_i, ft_atoi(tokens[1]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[2]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[3]) - 1);
		}
		else if (index_count[0] == 2)
		{
			toks[0] = ft_strsplit(tokens[1], '/');
			toks[1] = ft_strsplit(tokens[2], '/');
			toks[2] = ft_strsplit(tokens[3], '/');
			push_tri_index_data(&data->positions_i, toks, 0);
			if (data->texcoords.length > 0)
				push_tri_index_data(&data->texcoords_i, toks, 1);
			else if (data->normals.length > 0)
				push_tri_index_data(&data->normals_i, toks, 1);
			else
				error("Model parser error: Invalid normals or texcoords !");
			ft_tabdel(&toks[0]);
			ft_tabdel(&toks[1]);
			ft_tabdel(&toks[2]);
		}
		else if (index_count[0] == 3)
		{
			toks[0] = ft_strsplit(tokens[1], '/');
			toks[1] = ft_strsplit(tokens[2], '/');
			toks[2] = ft_strsplit(tokens[3], '/');
			push_tri_index_data(&data->positions_i, toks, 0);
			push_tri_index_data(&data->texcoords_i, toks, 1);
			push_tri_index_data(&data->normals_i, toks, 2);
			ft_tabdel(&toks[0]);
			ft_tabdel(&toks[1]);
			ft_tabdel(&toks[2]);
		}
		else
			error("Model parser error: Invalid indices format !");
		data->size += 3;
	}
	else if (tokens[1] && tokens[2] && tokens[3] && tokens[4])
	{
		index_count[0] = get_index_count(tokens[1]);
		if (index_count[0] == 1)
		{
			buff_push_uint(&data->positions_i, ft_atoi(tokens[1]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[2]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[3]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[1]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[3]) - 1);
			buff_push_uint(&data->positions_i, ft_atoi(tokens[4]) - 1);
		}
		else if (index_count[0] == 2)
		{
			toks[0] = ft_strsplit(tokens[1], '/');
			toks[1] = ft_strsplit(tokens[2], '/');
			toks[2] = ft_strsplit(tokens[3], '/');
			toks[3] = ft_strsplit(tokens[4], '/');
			push_quad_index_data(&data->positions_i, toks, 0);
			if (data->texcoords.length > 0)
				push_quad_index_data(&data->texcoords_i, toks, 1);
			else if (data->normals.length > 0)
				push_quad_index_data(&data->normals_i, toks, 1);
			else
				error("Model parser error: Invalid normals or texcoords !");
			ft_tabdel(&toks[0]);
			ft_tabdel(&toks[1]);
			ft_tabdel(&toks[2]);
			ft_tabdel(&toks[3]);
		}
		else if (index_count[0] == 3)
		{
			toks[0] = ft_strsplit(tokens[1], '/');
			toks[1] = ft_strsplit(tokens[2], '/');
			toks[2] = ft_strsplit(tokens[3], '/');
			toks[3] = ft_strsplit(tokens[4], '/');
			push_quad_index_data(&data->positions_i, toks, 0);
			push_quad_index_data(&data->texcoords_i, toks, 1);
			push_quad_index_data(&data->normals_i, toks, 2);
			ft_tabdel(&toks[0]);
			ft_tabdel(&toks[1]);
			ft_tabdel(&toks[2]);
			ft_tabdel(&toks[3]);
		}
		else
			error("Model parser error: Invalid indices format !");
		data->size += 6;
	}
	else
		error("Model parser error: Invalid indices !");
}

static void		parse_line(char *line, t_model_data *data)
{
	char			**tokens;

	if (!(tokens = ft_strsplit(line, ' ')))
		error("Model parser error: Invalid tokens !");
	if (tokens[0] && ft_strcmp(tokens[0], "v") == 0)
		parse_vertices(data, tokens);
	else if (tokens[0] && ft_strcmp(tokens[0], "vn") == 0)
		parse_normals(data, tokens);
	else if (tokens[0] && ft_strcmp(tokens[0], "vt") == 0)
		parse_texcoords(data, tokens);
	else if (tokens[0] && ft_strcmp(tokens[0], "f") == 0)
		parse_indces(data, tokens);
	ft_tabdel(&tokens);
}

t_glfloatbuffer init_vertices(t_glfloatbuffer *v, int size)
{
	t_glfloatbuffer result;

	if (!v->buffer)
		error("Model parser error: Invalid loaded vertices !");
	result.length = size * 3;
	result.size = sizeof(GLfloat) * result.length;
	if (!(result.buffer = (GLfloat *)malloc(result.size)))
		error("Malloc error !");
	return (result);
}

t_glfloatbuffer init_texcoords(t_glfloatbuffer *t, int size)
{
	t_glfloatbuffer result;

	if (t->buffer)
	{
		result.length = size * 2;
		result.size = sizeof(GLfloat) * result.length;
		if (!(result.buffer = (GLfloat *)malloc(result.size)))
			error("Malloc error !");
		return (result);
	}
	result.length = 0;
	result.size = 0;
	result.buffer = NULL;
	return (result);
}

t_glfloatbuffer init_normals(t_glfloatbuffer *n, int size)
{
	t_glfloatbuffer result;

	if (n->buffer)
	{
		result.length = size * 3;
		result.size = sizeof(GLfloat) * result.length;
		if (!(result.buffer = (GLfloat *)malloc(result.size)))
			error("Malloc error !");
		return (result);
	}
	result.length = 0;
	result.size = 0;
	result.buffer = NULL;
	return (result);
}

t_gluintbuffer init_indices(t_model_index *i, int size)
{
	t_gluintbuffer result;

	if (!i)
		error("Model parser error: Invalid loaded indices !");
	result.length = size;
	result.size = sizeof(GLfloat) * result.length;
	if (!(result.buffer = (GLuint *)malloc(result.size)))
		error("Malloc error !");
	return (result);
}

static t_mesh	*convert_to_mesh(t_model_data *data, t_model_index *i, int size)
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
		mesh_data.vertices.buffer[j * 3 + 0] = data->positions.buffer[i[j].position * 3 + 0];
		mesh_data.vertices.buffer[j * 3 + 1] = data->positions.buffer[i[j].position * 3 + 1];
		mesh_data.vertices.buffer[j * 3 + 2] = data->positions.buffer[i[j].position * 3 + 2];

		if (data->texcoords.buffer != NULL)
		{
			mesh_data.texcoords.buffer[j * 2 + 0] = data->texcoords.buffer[i[j].texture * 2 + 0];
			mesh_data.texcoords.buffer[j * 2 + 1] = data->texcoords.buffer[i[j].texture * 2 + 1];
		}
		if (data->normals.buffer != NULL)
		{
			mesh_data.normals.buffer[j * 3 + 0] = data->normals.buffer[i[j].normal * 3 + 0];
			mesh_data.normals.buffer[j * 3 + 1] = data->normals.buffer[i[j].normal * 3 + 1];
			mesh_data.normals.buffer[j * 3 + 2] = data->normals.buffer[i[j].normal * 3 + 2];
		}

		mesh_data.indices.buffer[j] = j;
	}
	return new_mesh(&mesh_data);
}

static t_model_index *get_indices(t_model_data *data, int size)
{
	t_model_index	*result;
	int				i;

	if (!(result = (t_model_index *)malloc(sizeof(t_model_index) * (size))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i].position = data->positions_i.buffer[i];
		if (data->normals_i.buffer)
			result[i].normal = data->normals_i.buffer[i];
		if (data->texcoords_i.buffer)
			result[i].texture = data->texcoords_i.buffer[i];
		i++;
	}
	return (result);
}

t_mesh			*new_model(char *file)
{
	int				fd;
	char			*line;
	t_model_data	data;

	if ((fd = open(file, O_RDONLY)) < 0)
		error("Failed to load model !");
	data.positions = (t_glfloatbuffer){0, 0, NULL};
	data.texcoords = (t_glfloatbuffer){0, 0, NULL};
	data.normals = (t_glfloatbuffer){0, 0, NULL};
	data.positions_i = (t_gluintbuffer){0, 0, NULL};
	data.texcoords_i = (t_gluintbuffer){0, 0, NULL};
	data.normals_i = (t_gluintbuffer){0, 0, NULL};
	data.min_vertices = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	data.max_vertices = vec3(FLT_MIN, FLT_MIN, FLT_MIN);
	data.size = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &data);
		ft_strdel(&line);
	}
	close(fd);
	t_model_index *indices = get_indices(&data, data.size);
	t_mesh *m = convert_to_mesh(&data, indices, data.size);
	free(data.positions.buffer);
	free(data.texcoords.buffer);
	free(data.normals.buffer);
	free(data.positions_i.buffer);
	free(data.normals_i.buffer);
	free(data.texcoords_i.buffer);
	free(indices);
	return (m);
}
