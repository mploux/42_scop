/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:55:42 by mploux            #+#    #+#             */
/*   Updated: 2018/04/19 19:57:42 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strchrl(const char *s, int c)
{
	size_t i;

	i = ft_strlen(s) - 1;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		if (s[i + 1] == c)
			return ((char *)&s[i + 1]);
		i--;
	}
	return (NULL);
}
