/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 21:30:29 by mploux            #+#    #+#             */
/*   Updated: 2018/03/22 21:30:53 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int			get_mouse_button(t_input *input, int button)
{
	return (glfwGetMouseButton(input->window, button));
}

t_vec2		get_mouse_position(t_input *input)
{
	return (input->mouse_position);
}

t_vec2		get_mouse_velocity(t_input *input)
{
	return (input->mouse_velocity);
}
