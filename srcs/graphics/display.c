/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:06:20 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 15:05:05 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_display		init_display(const char *title, int width, int height)
{
	t_display	result;

	if (!glfwInit())
		error("Unable to init glfw !");
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	result.window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!result.window)
		error("Unable to init glfw window !");
	glfwMakeContextCurrent(result.window);
	glViewport(0, 0, 1280, 720);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		error("Unable to init glfw window !");
	glfwSwapInterval(0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	result.title = title;
	result.width = width;
	result.height = height;
	return (result);
}

void			clean_display(t_display *display)
{
	glfwDestroyWindow(display->window);
	glfwTerminate();
}
