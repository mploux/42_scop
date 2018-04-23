/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:51:41 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 16:43:31 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int		main(int av, char **ac)
{
	t_core	*core;

	if (av != 2 && av != 3)
		error("Usage: ./scop obj_model [texture]");
	core = new_core(ac[1], ac[2]);
	run_core(core);
	delete_core(&core);
	return (EXIT_SUCCESS);
}
