/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_indices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:49:27 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 17:51:46 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_gluintbuffer	init_indices(t_model_index *i, int size)
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

t_model_index	*get_indices(t_model_data *data, size_t size)
{
	t_model_index	*result;
	size_t			i;

	if (!(result = (t_model_index *)malloc(sizeof(t_model_index) * (size))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (i < data->positions_i.length)
			result[i].position = data->positions_i.buffer[i];
		if (data->normals_i.buffer && i < data->normals_i.length)
			result[i].normal = data->normals_i.buffer[i];
		if (data->texcoords_i.buffer && i < data->texcoords_i.length)
			result[i].texture = data->texcoords_i.buffer[i];
		i++;
	}
	return (result);
}
