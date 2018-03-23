/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 21:29:59 by mploux            #+#    #+#             */
/*   Updated: 2018/03/22 21:30:20 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int			get_key(t_input *input, int key)
{
	return (glfwGetKey(input->window, key));
}

int			get_key_up(t_input *input, int key)
{
	return (input->up_keys[key]);
}

int			get_key_down(t_input *input, int key)
{
	return (input->down_keys[key]);
}
