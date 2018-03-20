/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/03/04 18:11:03 by mploux           ###   ########.fr       */
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
		data->positions_size += 3;
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
		data->normals_size += 3;
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

		ft_putnbr(indices[0].position);
		ft_putstr(" ");
		ft_putnbr(indices[1].position);
		ft_putstr(" ");
		ft_putnbr(indices[2].position);
		ft_putstr("   ");


		ft_lstadd(&data->indices, ft_lstnew(&indices[0], sizeof(t_model_index)));
		ft_putnbr(((t_model_index *) data->indices->content)->position);
		ft_putstr(" ");
		ft_lstadd(&data->indices, ft_lstnew(&indices[1], sizeof(t_model_index)));
		ft_putnbr(((t_model_index *) data->indices->content)->position);
		ft_putstr(" ");
		ft_lstadd(&data->indices, ft_lstnew(&indices[2], sizeof(t_model_index)));
		ft_putnbr(((t_model_index *) data->indices->content)->position);
		ft_putstr("\n");
		data->size += 3;
	}
	ft_tabdel(&tokens);
}

static t_mesh	*convert_to_mesh(t_glfloatbuffer *v, t_glfloatbuffer *n, t_model_index *i, int size)
{
	int				j;

	t_glfloatbuffer	vertices;
	t_glfloatbuffer	normals;
	t_gluintbuffer	indices;

	j = -1;

	vertices.size = sizeof(GLfloat) * (size * 3);
	if (!(vertices.buffer = (GLfloat *)malloc(vertices.size)))
		return (NULL);
	normals.size = sizeof(GLfloat) * (size * 3);
	if (!(normals.buffer = (GLfloat *)malloc(normals.size)))
		return (NULL);
	indices.size = sizeof(GLuint) * (size);
	if (!(indices.buffer = (GLuint *)malloc(indices.size)))
		return (NULL);

	while (++j < size / 3)
	{
		vertices.buffer[j * 3 + 0] = v->buffer[i[j * 3 + 0].position];
		vertices.buffer[j * 3 + 1] = v->buffer[i[j * 3 + 1].position];

		ft_putnbr(i[j * 3 + 0].position);
		ft_putstr(" ");
		ft_putnbr(i[j * 3 + 1].position);
		ft_putstr(" ");
		ft_putnbr(i[j * 3 + 2].position);
		ft_putstr("\n");

		vertices.buffer[j * 3 + 2] = v->buffer[i[j * 3 + 2].position];

		normals.buffer[j * 3 + 0] = n->buffer[i[j * 3 + 0].normal];
		normals.buffer[j * 3 + 1] = n->buffer[i[j * 3 + 1].normal];
		normals.buffer[j * 3 + 2] = n->buffer[i[j * 3 + 2].normal];

		indices.buffer[j] = j;
	}

	return new_mesh(&vertices, &normals, &indices);
}

static t_model_index *get_indices(t_list *indices, int size)
{
	t_model_index	*result;
	t_list			*list;
	int				i;

	if (!(result = (t_model_index *)malloc(sizeof(t_model_index) * (size))))
		return (NULL);
	list = indices;
	i = 0;
	ft_putstr("\n");
	while (list)
	{
		t_model_index *index = (t_model_index *) list->content;
		result[i].position = index->position;
		result[i].normal = index->normal;
		result[i].texture = index->texture;

		ft_putnbr(index->position);

		if (i % 3 == 2)
			ft_putstr("\n");
		else
			ft_putstr(" ");
		list = list->next;
		i++;
	}
	return (result);
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
	t_model_index *indices = get_indices(data.indices, data.size);

	ft_putstr("\n\n");
	t_mesh *m = convert_to_mesh(&vertices, &normals, indices, data.size);
	ft_putstr("LOL 6\n");

	ft_lstclear(&data.positions);
	ft_lstclear(&data.normals);
	ft_lstclear(&data.indices);
	return (m);
}
