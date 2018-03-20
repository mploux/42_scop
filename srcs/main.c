/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:51:41 by mploux            #+#    #+#             */
/*   Updated: 2018/03/11 17:34:24 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "buffers.h"
#include "model.h"

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	t_shader *mainShader = new_shader("data/shaders/main.vert", "data/shaders/main.frag");
	// // t_mesh *model_42 = new_model("data/models/42.obj");
	t_mesh *box = new_model(ac[1]);

	int x, y, z;

	x = 0;
	y = 0;
	z = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(mainShader->program);
		x++;
		y++;
		z++;
		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "projectionMatrix"), 1, GL_FALSE, mat4_persp(70.0f, 640.0f / 480.0f, 0.1f, 100.0f).m);
		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "viewMatrix"), 1, GL_TRUE, mat4_mul(mat4_translate(vec3(0, 0, 5)), mat4_rotate_xyz(z * 0.003f, y * 0.003f, z * 0.003f)).m);
		draw(box);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// delete_shader(&mainShader);
	// delete_mesh(&model_42);
	delete_mesh(&box);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
