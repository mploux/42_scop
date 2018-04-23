/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:19:58 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 23:59:03 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_input		init_input(GLFWwindow *window)
{
	t_input result;
	int		i;

	result.window = window;
	i = -1;
	while (++i < KEYS_COUNT)
	{
		result.up_keys[i] = 0;
		result.down_keys[i] = 0;
		result.keys[i] = 0;
	}
	i = -1;
	while (++i < BUTTONS_COUNT)
		result.buttons[i] = 0;
	result.mouse_position = (t_vec2){0, 0};
	result.mouse_old_position = (t_vec2){0, 0};
	result.mouse_velocity = (t_vec2){0, 0};
	result.focused = 0;
	return (result);
}

void		input_update(t_input *input)
{
	int		i;

	i = -1;
	while (++i < KEYS_COUNT)
	{
		input->up_keys[i] = 0;
		if (!get_key(input, i) && input->keys[i])
			input->up_keys[i] = 1;
		input->down_keys[i] = 0;
		if (get_key(input, i) && !input->keys[i])
			input->down_keys[i] = 1;
		input->keys[i] = 0;
		if (get_key(input, i))
			input->keys[i] = 1;
	}
}

void		input_handle_focus(t_input *input)
{
	double	x;
	double	y;

	glfwGetCursorPos(input->window, &x, &y);
	if (get_mouse_button(input, 0) && !input->focused)
	{
		input->focused = 1;
		glfwSetInputMode(input->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(input->window, &x, &y);
	}
	else if (get_key_down(input, GLFW_KEY_ESCAPE) && input->focused)
	{
		input->focused = 0;
		glfwSetInputMode(input->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPos(input->window, 1280.0 / 2.0, 720.0 / 2.0);
	}
	if (input->focused)
	{
		input_handle_mouse(input, x, y);
	}
	else
	{
		input->mouse_old_position.x = x;
		input->mouse_old_position.y = y;
	}
}

void		input_handle_mouse(t_input *input, float x, float y)
{
	input->mouse_position.x = x;
	input->mouse_position.y = y;
	input->mouse_velocity.x = x - input->mouse_old_position.x;
	input->mouse_velocity.y = y - input->mouse_old_position.y;
	input->mouse_old_position.x = x;
	input->mouse_old_position.y = y;
}
