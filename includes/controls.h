/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:25:37 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 18:06:37 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "core.h"

typedef struct s_core	t_core;

void					handle_controls(t_core *c, float speed);
void					handle_render_controls(t_core *c, float speed);
void					handle_mouse_controls(t_core *c, float speed);
void					handle_camera_controls(t_core *c, float speed);
void					handle_rotation_controls(t_core *c, float speed);

#endif
