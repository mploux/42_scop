/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:51:41 by mploux            #+#    #+#             */
/*   Updated: 2018/03/21 14:17:54 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "buffers.h"
#include "model.h"
#include "texture.h"

int main(int av, char **ac)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1280, 720, "Scop", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (-1);
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, 1280, 720);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		return (-1);

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	t_shader *mainShader = new_shader("data/shaders/main.vert", "data/shaders/main.frag");
	// // t_mesh *model_42 = new_model("data/models/42.obj");
	t_texture *tex = new_texture(ac[2]);
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

		bind_texture(tex);

		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "projectionMatrix"), 1, GL_FALSE, mat4_persp(70.0f, 1280.0f / 720.0f, 0.1f, 100.0f).m);

		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "viewMatrix"), 1, GL_TRUE, mat4_mul(mat4_translate(vec3(0, 0, 3)), mat4_rotate_xyz(x * 0.03f, y * 0.00f, z * 0.00f)).m);
		draw(box);

		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "viewMatrix"), 1, GL_TRUE, mat4_mul(mat4_translate(vec3(-2, 0, 3)), mat4_rotate_xyz(x * 0.00f, y * 0.03f, z * 0.00f)).m);
		draw(box);

		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "viewMatrix"), 1, GL_TRUE, mat4_mul(mat4_translate(vec3(2, 0, 3)), mat4_rotate_xyz(x * 0.00f, y * 0.00f, z * 0.03f)).m);
		draw(box);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// delete_mesh(&model_42);
	delete_shader(&mainShader);
	delete_mesh(&box);
	delete_texture(&tex);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
