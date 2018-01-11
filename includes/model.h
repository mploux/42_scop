/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:06:53 by mploux            #+#    #+#             */
/*   Updated: 2018/01/11 20:46:58 by mploux           ###   ########.fr       */
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

typedef struct	s_model_data
{
	t_list	*positions;
	t_list	*normals;
	t_list	*indices;
	int		size;
}				t_model_data;

typedef struct	s_model_index
{
	int		position;
	int		normal;
}				t_model_index;

t_mesh			*new_model(char *file);

#endif
