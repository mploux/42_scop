/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:51:41 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 20:22:39 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int		main(int av, char **ac)
{
	t_core	*core;

	core = NULL;
	if (av == 2)
		core = new_core(ac[1], "data/textures/licorne.bmp");
	else if (av == 3)
		core = new_core(ac[1], ac[2]);
	else
		error("Usage: ./scop obj_model [texture]");
	run_core(core);
	delete_core(&core);
	return (EXIT_SUCCESS);
}
