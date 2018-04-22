/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:07:04 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 02:00:43 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H


# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "error.h"

typedef struct	s_display
{
	GLFWwindow	*window;
	const char	*title;
	int			width;
	int			height;
}				t_display;

t_display		init_display(const char *title, int width, int height);
void			clean_display(t_display *display);

#endif
