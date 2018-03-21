/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 21:39:10 by mploux            #+#    #+#             */
/*   Updated: 2018/03/21 09:41:18 by mploux           ###   ########.fr       */
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
	// write(1, header, 54);
	result->width = (int) (header[0x12] | (header[0x13] << 8) | (header[0x14] << 16) | (header[0x15] << 24));
	result->height = (int) (header[0x16] | (header[0x17] << 8) | (header[0x18] << 16) | (header[0x19] << 24));
	data_size = (int) (header[0x22] | (header[0x23] << 8) | (header[0x24] << 16) | (header[0x25] << 24));
	if (!(result->data = (unsigned char *)malloc(data_size)))
		return (NULL);
	read(fd, result->data, data_size);
	close(fd);

	// printf("Loading texture %s  %u %u  %u\n", result->data, result->width, result->height, data_size);

	// write(1, result->data, data_size);

	glGenTextures(1, &result->index);
	glBindTexture(GL_TEXTURE_2D, result->index);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, result->width, result->height, 0, GL_BGR, GL_UNSIGNED_BYTE, result->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);


	return (result);
}

int				delete_texture(t_texture **texture)
{
	if (texture == NULL || *texture == NULL)
		return (0);
	if ((*texture)->data != NULL)
		free((*texture)->data);
	free(*texture);
	*texture = NULL;
	return (1);
}

void			bind_texture(t_texture *texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->index);
}

void			unbind_texture()
{
	glBindTexture(GL_TEXTURE_2D, (unsigned int)0);
}
