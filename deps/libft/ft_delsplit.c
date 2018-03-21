/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 09:16:28 by mploux            #+#    #+#             */
/*   Updated: 2018/03/21 09:23:35 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delsplit(char ***split)
{
	int i;

	if (split == NULL || *split == NULL)
		return ;
	i = -1;
	while ((*split)[++i])
		ft_strdel(&(*split)[i]);
	free(*split);
	*split = NULL;
}
