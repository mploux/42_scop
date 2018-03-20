/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 21:39:10 by mploux            #+#    #+#             */
/*   Updated: 2018/03/20 22:30:07 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_texture		*new_texture(const char *path)
{
	t_texture		*result;
	int				fd;
	unsigned char	header[54];
	size_t			data_size;

	if (!(result = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	fd = open(path, O_RDONLY);
	read(fd, header, 54);
	result->width = *(int *)&(header[0x12]);
	result->height = *(int *)&(header[0x16]);
	data_size = sizeof(unsigned char) * (*(int *)&(header[0x22]));
	if (!(result->data = (unsigned char *)malloc(data_size)))
		return (NULL);
	read(fd, result->data, data_size);
	close(fd);
	return (result);
}

int				delete_texture(t_texture *texture)
{
	if (texture == NULL)
		return (0);
	if (texture->data != NULL)
		free(texture->data);
	free(texture);
	return (1);
}

void			bind_texture(t_texture *texture)
{

}

void			unbind_texture()
{

}
