/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:06:53 by mploux            #+#    #+#             */
/*   Updated: 2018/01/10 21:09:47 by mploux           ###   ########.fr       */
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

t_mesh			*new_model(char *file);

#endif
