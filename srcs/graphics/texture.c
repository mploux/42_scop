/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 21:39:10 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 19:07:21 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_texture		*new_texture(const char *path)
{
	t_texture		*result;

	if (!(result = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	if (!load_texture(result, path))
		return (NULL);
	glGenTextures(1, &result->index);
	glBindTexture(GL_TEXTURE_2D, result->index);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, result->width, result->height,
									0, GL_BGR, GL_UNSIGNED_BYTE, result->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
													GL_LINEAR_MIPMAP_LINEAR);
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

int				load_texture(t_texture *tex, const char *path)
{
	int				fd;
	unsigned char	h[54];
	size_t			data_size;

	ft_putstr("loading: ");
	ft_putstr(path);
	ft_putstr("\n");
	if ((fd = open(path, O_RDONLY)) < 0)
		error("Texture loader: Unable to open file !");
	if (!read(fd, h, 54))
		error("Texture loader: Unable to read file !");
	if (h[0] != 'B' || h[1] != 'M')
		error("Texture loader: Invalid BMP format !");
	tex->width = as_int(h[0x12], h[0x13], h[0x14], h[0x15]);
	tex->height = as_int(h[0x16], h[0x17], h[0x18], h[0x19]);
	data_size = as_int(h[0x22], h[0x23], h[0x24], h[0x25]);
	if ((size_t)(tex->width * tex->height * 3) != data_size)
		error("Texture loader: Invalid file format !");
	if (!(tex->data = (unsigned char *)malloc(data_size)))
		return (0);
	if (!read(fd, tex->data, data_size))
		error("Texture loader: Unable to read file !");
	close(fd);
	return (1);
}

void			bind_texture(t_texture *texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->index);
}

void			unbind_texture(void)
{
	glBindTexture(GL_TEXTURE_2D, (unsigned int)0);
}
