/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:35:53 by mploux            #+#    #+#             */
/*   Updated: 2018/03/03 18:12:37 by mploux           ###   ########.fr       */
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
	GLuint			nbo;
	GLuint			ibo;
	t_glfloatbuffer	vertices;
	t_glfloatbuffer	normals;
	t_gluintbuffer	indices;
};

typedef struct		s_mesh t_mesh;

t_mesh				*new_mesh(t_glfloatbuffer *v, t_glfloatbuffer *n, t_gluintbuffer *i);
void				delete_mesh(t_mesh **mesh);
void				draw(t_mesh *mesh);

#endif
