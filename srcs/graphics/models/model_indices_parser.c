/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_indices_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:59:18 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 18:04:49 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void	push_positions(t_model_data *data, char **tokens, int id[3])
{
	int	i;
	int	index;

	i = -1;
	while (++i < 3)
	{
		index = parse_index_pos(tokens[id[i]]) - 1;
		if (index >= 0)
			buff_push_uint(&data->positions_i, index);
	}
}

static void	push_texcoords(t_model_data *data, char **tokens, int id[3])
{
	int	i;
	int	index;

	i = -1;
	while (++i < 3)
	{
		index = parse_index_uv(tokens[id[i]]) - 1;
		if (index >= 0)
			buff_push_uint(&data->texcoords_i, index);
	}
}

static void	push_normals(t_model_data *data, char **tokens, int id[3])
{
	int	i;
	int	index;

	i = -1;
	while (++i < 3)
	{
		index = parse_index_normal(tokens[id[i]]) - 1;
		if (index >= 0)
			buff_push_uint(&data->normals_i, index);
	}
}

void		parse_indces(t_model_data *data, char **tokens)
{
	int		id[3];
	int		size;
	int		i;

	size = -1;
	i = 0;
	while (tokens[++size])
		if (i > 16)
			error("Model parser error: Invalid indices count !");
	while (i < size - 1)
	{
		id[0] = (i / 6) + 1;
		id[1] = (i / 3) + 2;
		id[2] = (i / 3) + 3;
		push_positions(data, tokens, id);
		push_texcoords(data, tokens, id);
		push_normals(data, tokens, id);
		data->size += 3;
		i += 3;
	}
}
