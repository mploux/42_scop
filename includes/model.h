/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:06:53 by mploux            #+#    #+#             */
/*   Updated: 2018/03/25 13:50:29 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H
# define MODEL_H

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>
# include <float.h>

# include "error.h"
# include "maths.h"
# include "buffers.h"
# include "mesh.h"

typedef struct		s_mesh t_mesh;

typedef struct		s_model_data
{
	t_glfloatbuffer	positions;
	t_glfloatbuffer	texcoords;
	t_glfloatbuffer	normals;
	t_gluintbuffer	indices;
	t_gluintbuffer	positions_i;
	t_gluintbuffer	texcoords_i;
	t_gluintbuffer	normals_i;
	t_vec3			min_vertices;
	t_vec3			max_vertices;
	int				size;
	int				index_count;
}					t_model_data;

typedef struct		s_model_index
{
	int				position;
	int				normal;
	int				texture;
}					t_model_index;

t_mesh				*new_model(char *file);

#endif
