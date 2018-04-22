/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_v_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:44:21 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 18:20:14 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_glfloatbuffer	init_vertices(t_glfloatbuffer *v, int size)
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

void			parse_vertices(t_model_data *data, char **tokens)
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

int				parse_index_pos(char *index)
{
	int		result;
	char	*data;
	int		size;
	int		i;

	if (index == NULL)
		return (-1);
	size = 0;
	while (index[size] != '/' && index[size] != '\n' && index[size] != 0)
		size++;
	if (size == 0)
		return (-1);
	if (!(data = ft_strnew(size)))
		error("Malloc error !");
	i = -1;
	while (++i < size)
		data[i] = index[i];
	result = ft_atoi(data);
	ft_strdel(&data);
	return (result);
}
