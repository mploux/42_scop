/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:35:53 by mploux            #+#    #+#             */
/*   Updated: 2018/03/22 22:04:17 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include <GL/glew.h>

# include "error.h"
# include "maths.h"
# include "buffers.h"
# include "model.h"

struct		s_mesh
{
	GLuint			vao;
	GLuint			vbo;
	GLuint			tbo;
	GLuint			nbo;
	GLuint			cbo;
	GLuint			ibo;
	t_glfloatbuffer	vertices;
	t_glfloatbuffer	texcoords;
	t_glfloatbuffer	normals;
	t_glfloatbuffer	colors;
	t_gluintbuffer	indices;
};

typedef struct		s_mesh t_mesh;

t_mesh				*new_mesh(t_glfloatbuffer *v, t_glfloatbuffer *t, t_glfloatbuffer *n, t_gluintbuffer *i);
t_glfloatbuffer		generate_colors(t_glfloatbuffer *v);
void				delete_mesh(t_mesh **mesh);
void				draw(t_mesh *mesh);

#endif
