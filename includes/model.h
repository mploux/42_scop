/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:06:53 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 17:29:21 by mploux           ###   ########.fr       */
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

typedef struct s_mesh	t_mesh;

typedef struct			s_model_data
{
	t_glfloatbuffer		positions;
	t_glfloatbuffer		texcoords;
	t_glfloatbuffer		normals;
	t_gluintbuffer		indices;
	t_gluintbuffer		positions_i;
	t_gluintbuffer		texcoords_i;
	t_gluintbuffer		normals_i;
	t_vec3				min_vertices;
	t_vec3				max_vertices;
	int					size;
	int					index_count;
}						t_model_data;

typedef struct			s_model_index
{
	int					position;
	int					normal;
	int					texture;
}						t_model_index;

t_mesh					*new_model(char *file);
t_mesh					*convert_to_mesh(t_model_data *data, t_model_index *i,
																int size);

t_gluintbuffer			init_indices(t_model_index *i, int size);
t_glfloatbuffer			init_normals(t_glfloatbuffer *n, int size);
t_glfloatbuffer			init_texcoords(t_glfloatbuffer *t, int size);
t_glfloatbuffer			init_vertices(t_glfloatbuffer *v, int size);
void					parse_line(char *line, t_model_data *data);
void					parse_indces(t_model_data *data, char **tokens);
int						parse_index_normal(char *index);
int						parse_index_uv(char *index);
int						parse_index_pos(char *index);
void					parse_texcoords(t_model_data *data, char **tokens);
void					parse_normals(t_model_data *data, char **tokens);
void					parse_vertices(t_model_data *data, char **tokens);
t_model_index			*get_indices(t_model_data *data, size_t size);

#endif
