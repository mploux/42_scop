/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:45:25 by mploux            #+#    #+#             */
/*   Updated: 2018/01/07 16:18:20 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char		*load_file(const char *name)
{
	int		fd;
	int		read_size;
	char	read_buff[1024 + 1];
	char	*result;
	char	*tmp;

	fd = 0;
	ft_putstr("loading: ");
	ft_putstr(name);
	ft_putstr("\n");
	if (name == NULL || (fd = open(name, O_RDONLY)) == -1)
		ft_putstr("unable to load file !");
	result = NULL;
	while ((read_size = read(fd, read_buff, 1024)) != 0)
	{
		tmp = result;
		read_buff[read_size] = 0;
		result = ft_strjoin(result, read_buff);
		free(tmp);
	}
	return (result);
}
