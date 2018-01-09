/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:18:01 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 21:18:12 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrev(t_list **lst)
{
	t_list	*l_prev;
	t_list	*l_cur;
	t_list	*l_next;

	l_prev = NULL;
	if (lst)
	{
		l_cur = *lst;
		while (l_cur)
		{
			l_next = l_cur->next;
			l_cur->next = l_prev;
			l_prev = l_cur;
			l_cur = l_next;
		}
		*lst = l_prev;
	}
	return (l_prev);
}
