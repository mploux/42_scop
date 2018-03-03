/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/03/03 18:04:12 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void		parse_line(char *line, t_model_data *data)
{
	char			**tokens;
	GLfloat			vertices[3];
	GLfloat			normals[3];
	t_model_index	indices[3];

	if (!(tokens = ft_strsplit(line, ' ')))
		error("Model parser error: Invalid tokens !");
	if (tokens[0] && ft_strcmp(tokens[0], "v") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");
		vertices[0] = atof(tokens[1]);
		vertices[1] = atof(tokens[2]);
		vertices[2] = atof(tokens[3]);
		ft_lstadd(&data->positions, ft_lstnew(&vertices[0], sizeof(GLfloat)));
		ft_lstadd(&data->positions, ft_lstnew(&vertices[1], sizeof(GLfloat)));
		ft_lstadd(&data->positions, ft_lstnew(&vertices[2], sizeof(GLfloat)));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "vn") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");
		normals[0] = atof(tokens[1]);
		normals[1] = atof(tokens[2]);
		normals[2] = atof(tokens[3]);
		ft_lstadd(&data->normals, ft_lstnew(&normals[0], sizeof(GLfloat)));
		ft_lstadd(&data->normals, ft_lstnew(&normals[1], sizeof(GLfloat)));
		ft_lstadd(&data->normals, ft_lstnew(&normals[2], sizeof(GLfloat)));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "f") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");

		char **toks1 = ft_strsplit(tokens[1], '/');
		char **toks2 = ft_strsplit(tokens[2], '/');
		char **toks3 = ft_strsplit(tokens[3], '/');

		indices[0].position = ft_atoi(toks1[0]) - 1;
		indices[0].normal 	= ft_atoi(toks1[2]) - 1;

		indices[1].position = ft_atoi(toks2[0]) - 1;
		indices[1].normal 	= ft_atoi(toks2[2]) - 1;

		indices[2].position = ft_atoi(toks3[0]) - 1;
		indices[2].normal 	= ft_atoi(toks3[2]) - 1;

		ft_lstadd(&data->indices, ft_lstnew(&indices[0], sizeof(GLuint)));
		ft_lstadd(&data->indices, ft_lstnew(&indices[1], sizeof(GLuint)));
		ft_lstadd(&data->indices, ft_lstnew(&indices[2], sizeof(GLuint)));

		data->size += 3;
	}
	ft_tabdel(&tokens);
}

static t_mesh	*convert_to_mesh(t_glfloatbuffer vertices, t_glfloatbuffer normals, t_gluintbuffer indices)
{
	int				i;

	t_glfloatbuffer	vertices;
	t_glfloatbuffer	normals;
	t_gluintbuffer	indices;

	t_mesh			result;
	t_model_index	index



	i = 0;
	while (++i < data.size)
	{
		index = *((t_model_index *)data.indices.content);

		vertices.buffer[i * 3 + 0] = data.positions[index.position * 3 + 0];
		vertices.buffer[i * 3 + 1] = data.positions[index.position * 3 + 1];
		vertices.buffer[i * 3 + 2] = data.positions[index.position * 3 + 2];

		normals.buffer[i * 3 + 0] = data.normals[index.normal * 3 + 0];
		normals.buffer[i * 3 + 1] = data.normals[index.normal * 3 + 1];
		normals.buffer[i * 3 + 2] = data.normals[index.normal * 3 + 2];

		indices.buffer[i] = i;

		data.indices = data.indices.next;
	}
}

t_mesh			*new_model(char *file)
{
	int				fd;
	char			*line;
	t_model_data	data;

	fd = open(file, O_RDONLY);
	data.positions = NULL;
	data.normals = NULL;
	data.indices = NULL;
	data.size = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &data);
		ft_strdel(&line);
	}
	t_glfloatbuffer vertices = ltfb(data.positions);
	t_glfloatbuffer normals = ltfb(data.normals);
	t_model_index indices = ltib(data.indices);
	ft_lstclear(&data.positions);
	ft_lstclear(&data.normals);
	ft_lstclear(&data.indices);
	return (new_mesh(&vertices, &normals, &indices));
}
