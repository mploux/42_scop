/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:13:33 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 02:03:29 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <libft.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <time.h>

# include "display.h"
# include "shader.h"
# include "mesh.h"
# include "buffers.h"
# include "model.h"
# include "texture.h"
# include "input.h"
# include "controls.h"
# include "camera.h"
# include "entity.h"

struct					s_core
{
	t_display			display;
	t_input				input;
	t_camera			camera;
	t_shader			*shader;
	t_texture			*texture;
	t_mesh				*model;
	t_mesh				*ground;
	t_list				*entities;
	t_vec3				model_pos;
	t_vec3				model_rot;
	t_vec3				model_scale;
	t_mat4				model_trs;
	t_mat4				model_centered_trs;
	t_vec3				rot_factor;
	float				use_texcoord;
	float				use_texture;
	float				use_normal;
	int					show_ground;
	t_vec3				light_pos;
};

typedef struct s_core	t_core;

t_core					init_core(int av, char **ac);
void					clean_core(t_core *core);
void					run_core(t_core *core);
void					update(t_core *core);
void					render(t_core *core);

#endif