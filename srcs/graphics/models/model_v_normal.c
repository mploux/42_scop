/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_v_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:48:19 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 16:32:03 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_glfloatbuffer	init_normals(t_glfloatbuffer *n, int size)
{
	t_glfloatbuffer	result;

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

void			parse_normals(t_model_data *data, char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		error("Model parser error: Invalid normals !");
	buff_push_float(&data->normals, atof(tokens[1]));
	buff_push_float(&data->normals, atof(tokens[2]));
	buff_push_float(&data->normals, atof(tokens[3]));
}

int				parse_index_normal(char *index)
{
	int		result;
	char	*data;
	char	*start;
	int		size;
	int		i;

	if (index == NULL)
		return (-1);
	size = 1;
	if (!(start = ft_strchrl(index, '/')))
		return (-1);
	while (start[size] != '/' && start[size] != '\n' && start[size] != 0)
		size++;
	size--;
	if (size == 0)
		return (-1);
	if (!(data = ft_strnew(size)))
		error("Malloc error !");
	i = -1;
	while (++i < size)
		data[i] = start[i + 1];
	result = ft_atoi(data);
	ft_strdel(&data);
	return (result);
}
