/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:06:53 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 21:11:55 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H
# define MODEL_H

#include "error.h"
#include "maths.h"
#include <libft.h>
#include <fcntl.h>
#include "buffers.h"
#include "mesh.h"

static void		parse_line(
	char *line,
	t_list **positions_list,
	t_list **indices_list);
	
t_mesh			*model(char *file);

#endif
