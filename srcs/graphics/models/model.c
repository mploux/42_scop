/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 20:38:56 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

void		parse_line(char *line, t_model_data *data)
{
	char	**tokens;

	if (!ft_isascii(line[0]))
		error("Model parser error: Invalid format !");
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

static void	init_model(t_model_data *data)
{
	data->positions = (t_glfloatbuffer){0, 0, NULL};
	data->texcoords = (t_glfloatbuffer){0, 0, NULL};
	data->normals = (t_glfloatbuffer){0, 0, NULL};
	data->positions_i = (t_gluintbuffer){0, 0, NULL};
	data->texcoords_i = (t_gluintbuffer){0, 0, NULL};
	data->normals_i = (t_gluintbuffer){0, 0, NULL};
	data->min_vertices = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	data->max_vertices = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	data->max_dim = FLT_MAX;
	data->size = 0;
}

static void	clean_model(t_model_data *data)
{
	free(data->positions.buffer);
	free(data->texcoords.buffer);
	free(data->normals.buffer);
	free(data->positions_i.buffer);
	free(data->normals_i.buffer);
	free(data->texcoords_i.buffer);
}

t_mesh		*new_model(char *file)
{
	int				fd;
	char			*line;
	t_model_data	data;
	t_model_index	*indices;
	t_mesh			*m;

	ft_putstr("loading: ");
	ft_putstr(file);
	ft_putstr("\n");
	if ((fd = open(file, O_RDONLY)) < 0)
		error("Failed to load model !");
	init_model(&data);
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &data);
		ft_strdel(&line);
	}
	close(fd);
	indices = get_indices(&data, data.size);
	m = convert_to_mesh(&data, indices, data.size);
	clean_model(&data);
	free(indices);
	return (m);
}
