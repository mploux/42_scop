/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:51:41 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 19:50:00 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "buffers.h"

int main(int av, char **ac)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Scop", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (-1);
	}

	glfwSwapInterval(0);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 640, 480);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		return (-1);

	t_shader *mainShader = new_shader("data/shaders/main.vert", "data/shaders/main.frag");

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		0.5f, 0.5f, 0,
		-0.5f, 0.5f, 0
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	t_glfloatbuffer verticesBuffer = {sizeof(vertices), vertices};
	t_gluintbuffer indicesBuffer = {sizeof(indices), indices};

	t_mesh *mesh = new_mesh(verticesBuffer, indicesBuffer);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5, 0, 0, 1);


		glUseProgram(mainShader->program);
		draw(mesh);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
