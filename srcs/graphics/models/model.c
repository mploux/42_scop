/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/03/23 11:46:40 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void		parse_vertices(t_model_data *data, char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		error("Model parser error: Invalid vertices !");
	buff_push_float(&data->positions, atof(tokens[1]));
	buff_push_float(&data->positions, atof(tokens[2]));
	buff_push_float(&data->positions, atof(tokens[3]));
}

static void		parse_normals(t_model_data *data, char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		error("Model parser error: Invalid normals !");
	// buff_push_float(&data->normals, atof(tokens[1]));
	// buff_push_float(&data->normals, atof(tokens[2]));
	// buff_push_float(&data->normals, atof(tokens[3]));
}

static void		parse_texcoords(t_model_data *data, char **tokens)
{
	if (!tokens[1] || !tokens[2])
		error("Model parser error: Invalid texcoords !");
	// buff_push_float(&data->texcoords, atof(tokens[1]));
	// buff_push_float(&data->texcoords, atof(tokens[2]));
}

static int		get_index_config(char *index)
{
	int		result;
	int		i;
	int		i_pos[3] = {-1, -1, -1};
	int		j;

	i = -1;
	j = -1;
	result = 0x001;
	while (index[++i])
	{
		printf("%c ", index[i]);
		if (index[i] == '/' || index[i + 1] == 0)
			i_pos[++j] = i;
	}
	printf("    %s %i %i %i\n", index, i_pos[0], i_pos[1], i_pos[2]);
	return (0);
}

static void		parse_indces(t_model_data *data, char **tokens)
{
	// char		**toks1;
	// char		**toks2;
	// char		**toks3;

	if (tokens[1] && tokens[2] && tokens[3] && !tokens[4])
	{
		get_index_config(tokens[1]);

		buff_push_uint(&data->positions_i, ft_atoi(tokens[1]) - 1);
		buff_push_uint(&data->positions_i, ft_atoi(tokens[2]) - 1);
		buff_push_uint(&data->positions_i, ft_atoi(tokens[3]) - 1);
		data->size += 3;
	}
	else if (tokens[1] && tokens[2] && tokens[3] && tokens[4])
	{
		get_index_config(tokens[1]);

		buff_push_uint(&data->positions_i, ft_atoi(tokens[1]) - 1);
		buff_push_uint(&data->positions_i, ft_atoi(tokens[2]) - 1);
		buff_push_uint(&data->positions_i, ft_atoi(tokens[3]) - 1);

		buff_push_uint(&data->positions_i, ft_atoi(tokens[1]) - 1);
		buff_push_uint(&data->positions_i, ft_atoi(tokens[3]) - 1);
		buff_push_uint(&data->positions_i, ft_atoi(tokens[4]) - 1);
		data->size += 6;
	}
	else
		error("Model parser error: Invalid indices !");
	// toks1 = ft_strsplit(tokens[1], '/');
	// toks2 = ft_strsplit(tokens[2], '/');
	// toks3 = ft_strsplit(tokens[3], '/');


	// buff_push_uint(&data->positions_i, ft_atoi(toks1[0]) - 1);
	// buff_push_uint(&data->texcoords_i, ft_atoi(toks1[1]) - 1);
	// buff_push_uint(&data->normals_i, ft_atoi(toks1[2]) - 1);
	//
	// buff_push_uint(&data->positions_i, ft_atoi(toks2[0]) - 1);
	// buff_push_uint(&data->texcoords_i, ft_atoi(toks2[1]) - 1);
	// buff_push_uint(&data->normals_i, ft_atoi(toks2[2]) - 1);
	//
	// buff_push_uint(&data->positions_i, ft_atoi(toks3[0]) - 1);
	// buff_push_uint(&data->texcoords_i, ft_atoi(toks3[1]) - 1);
	// buff_push_uint(&data->normals_i, ft_atoi(toks3[2]) - 1);

	// ft_tabdel(&toks1);
	// ft_tabdel(&toks2);
	// ft_tabdel(&toks3);
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

static t_mesh	*convert_to_mesh(t_glfloatbuffer *v, t_glfloatbuffer *t, t_glfloatbuffer *n, t_model_index *i, int size)
{
	int				j;
	t_glfloatbuffer	vertices;
	t_glfloatbuffer	texcoords;
	t_glfloatbuffer	normals;
	t_gluintbuffer	indices;

	j = -1;
	vertices = init_vertices(v, size);
	texcoords = init_texcoords(t, size);
	normals = init_normals(n, size);
	indices = init_indices(i, size);

	while (++j < size)
	{
		vertices.buffer[j * 3 + 0] = v->buffer[i[j].position * 3 + 0];
		vertices.buffer[j * 3 + 1] = v->buffer[i[j].position * 3 + 1];
		vertices.buffer[j * 3 + 2] = v->buffer[i[j].position * 3 + 2];

		if (t->buffer != NULL)
		{
			texcoords.buffer[j * 2 + 0] = t->buffer[i[j].texture * 2 + 0];
			texcoords.buffer[j * 2 + 1] = t->buffer[i[j].texture * 2 + 1];
		}
		if (n->buffer != NULL)
		{
			normals.buffer[j * 3 + 0] = n->buffer[i[j].normal * 3 + 0];
			normals.buffer[j * 3 + 1] = n->buffer[i[j].normal * 3 + 1];
			normals.buffer[j * 3 + 2] = n->buffer[i[j].normal * 3 + 2];
		}

		indices.buffer[j] = j;
	}
	return new_mesh(&vertices, &texcoords, &normals, &indices);
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
	data.size = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &data);
		ft_strdel(&line);
	}
	close(fd);
	t_model_index *positions_i = get_indices(&data, data.size);
	t_mesh *m = convert_to_mesh(&data.positions, &data.texcoords, &data.normals, positions_i, data.size);
	free(data.positions.buffer);
	free(data.texcoords.buffer);
	free(data.normals.buffer);
	free(data.positions_i.buffer);
	free(positions_i);
	return (m);
}
