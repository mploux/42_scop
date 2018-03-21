/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/03/21 13:47:07 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void		parse_line(char *line, t_model_data *data)
{
	char			**tokens;
	char			**toks1;
	char			**toks2;
	char			**toks3;

	if (!(tokens = ft_strsplit(line, ' ')))
		error("Model parser error: Invalid tokens !");
	if (tokens[0] && ft_strcmp(tokens[0], "v") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid vertices !");
		buff_push_float(&data->positions, atof(tokens[1]));
		buff_push_float(&data->positions, atof(tokens[2]));
		buff_push_float(&data->positions, atof(tokens[3]));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "vn") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid normals !");
		buff_push_float(&data->normals, atof(tokens[1]));
		buff_push_float(&data->normals, atof(tokens[2]));
		buff_push_float(&data->normals, atof(tokens[3]));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "vt") == 0)
	{
		if (!tokens[1] || !tokens[2])
			error("Model parser error: Invalid texcoords !");
		buff_push_float(&data->texcoords, atof(tokens[1]));
		buff_push_float(&data->texcoords, atof(tokens[2]));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "f") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid indices !");
		toks1 = ft_strsplit(tokens[1], '/');
		toks2 = ft_strsplit(tokens[2], '/');
		toks3 = ft_strsplit(tokens[3], '/');
		buff_push_uint(&data->indices, ft_atoi(toks1[0]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks1[1]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks1[2]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks2[0]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks2[1]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks2[2]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks3[0]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks3[1]) - 1);
		buff_push_uint(&data->indices, ft_atoi(toks3[2]) - 1);
		ft_tabdel(&toks1);
		ft_tabdel(&toks2);
		ft_tabdel(&toks3);
		data->size += 3;
	}
	else
	{
		ft_putstr(line);
		ft_putstr("\n");
	}
	ft_tabdel(&tokens);
}

static t_mesh	*convert_to_mesh(t_glfloatbuffer *v, t_glfloatbuffer *t, t_glfloatbuffer *n, t_model_index *i, int size)
{
	int				j;
	t_glfloatbuffer	vertices;
	t_glfloatbuffer	texcoords;
	t_glfloatbuffer	normals;
	t_gluintbuffer	indices;

	j = -1;
	vertices.size = sizeof(GLfloat) * (size * 3);
	if (!(vertices.buffer = (GLfloat *)malloc(vertices.size)))
		return (NULL);
	texcoords.size = sizeof(GLfloat) * (size * 2);
	if (!(texcoords.buffer = (GLfloat *)malloc(texcoords.size)))
		return (NULL);
	normals.size = sizeof(GLfloat) * (size * 3);
	if (!(normals.buffer = (GLfloat *)malloc(normals.size)))
		return (NULL);
	indices.size = sizeof(GLuint) * (size);
	if (!(indices.buffer = (GLuint *)malloc(indices.size)))
		return (NULL);
	while (++j < size)
	{
		vertices.buffer[j * 3 + 0] = v->buffer[i[j].position * 3 + 0];
		vertices.buffer[j * 3 + 1] = v->buffer[i[j].position * 3 + 1];
		vertices.buffer[j * 3 + 2] = v->buffer[i[j].position * 3 + 2];

		texcoords.buffer[j * 2 + 0] = t->buffer[i[j].texture * 2 + 0];
		texcoords.buffer[j * 2 + 1] = t->buffer[i[j].texture * 2 + 1];

		normals.buffer[j * 3 + 0] = n->buffer[i[j].normal * 3 + 0];
		normals.buffer[j * 3 + 1] = n->buffer[i[j].normal * 3 + 1];
		normals.buffer[j * 3 + 2] = n->buffer[i[j].normal * 3 + 2];

		indices.buffer[j] = j;
	}

	ft_putstr("\nfinit ! \n");

	return new_mesh(&vertices, &texcoords, &normals, &indices);
}

static t_model_index *get_indices(t_gluintbuffer *indices, int size)
{
	t_model_index	*result;
	int				i;

	if (!(result = (t_model_index *)malloc(sizeof(t_model_index) * (size))))
		return (NULL);
	i = 0;
	ft_putstr("\n");
	while (i < size)
	{
		result[i].position = indices->buffer[i * 3 + 0];
		result[i].texture = indices->buffer[i * 3 + 1];
		result[i].normal = indices->buffer[i * 3 + 2];
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
	data.indices = (t_gluintbuffer){0, 0, NULL};
	data.size = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &data);
		ft_strdel(&line);
	}
	close(fd);

	t_model_index *indices = get_indices(&data.indices, data.size);
	ft_putstr("\n");
	t_mesh *m = convert_to_mesh(&data.positions, &data.texcoords, &data.normals, indices, data.size);
	free(data.positions.buffer);
	free(data.texcoords.buffer);
	free(data.normals.buffer);
	free(data.indices.buffer);
	free(indices);
	return (m);
}
