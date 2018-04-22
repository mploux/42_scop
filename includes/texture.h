/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 21:25:09 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 17:22:24 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <GL/glew.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "int_utils.h"

typedef struct		s_texture
{
	GLuint			index;
	int				width;
	int				height;
	unsigned char	*data;
}					t_texture;

t_texture			*new_texture(const char *path);
int					delete_texture(t_texture **texture);

int					load_texture(t_texture *tex, const char *path);

void				bind_texture(t_texture *texture);
void				unbind_texture(void);

#endif
