/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:20:10 by mploux            #+#    #+#             */
/*   Updated: 2018/03/22 21:22:35 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define KEYS_COUNT 1024
# define BUTTONS_COUNT 3

# include <GLFW/glfw3.h>
# include "maths.h"

typedef struct	s_input
{
	GLFWwindow	*window;
	int			keys[KEYS_COUNT];
	int			up_keys[KEYS_COUNT];
	int			down_keys[KEYS_COUNT];
	int			buttons[BUTTONS_COUNT];
	t_vec2		mouse_position;
	t_vec2		mouse_old_position;
	t_vec2		mouse_velocity;
	int			focused;
}				t_input;

t_input			init_input(GLFWwindow *window);

void			input_update(t_input *input);
void			input_handle_focus(t_input *input);

void			read_keys(t_input *input);
void			read_buttons(t_input *input);

int				get_key(t_input *input, int key);
int				get_key_up(t_input *input, int key);
int				get_key_down(t_input *input, int key);

int				get_mouse_button(t_input *input, int button);
t_vec2			get_mouse_position(t_input *input);
t_vec2			get_mouse_velocity(t_input *input);

#endif
