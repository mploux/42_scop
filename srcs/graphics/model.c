/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/01/09 19:54:23 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "maths.h"
#include <libft.h>

static void		parse_line(
	char *line,
	t_list **positions_list,
	t_list **indices_list)
{
	char	**tokens;
	t_vec3	val;
	int		indices[3];

	if (!(tokens = ft_strsplit(line, ' ')))
		error("Model parser error: Invalid tokens !");
	if (tokens[0] && ft_strcmp(tokens[0], "v") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");
		val = vec3(atof(tokens[1]), atof(tokens[2]), atof(tokens[3]));
		ft_lstadd(positions_list, ft_lstnew(&val, sizeof(t_vec3)));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "f") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");
		indices[0] = ft_atoi(tokens[1]) - 1;
		indices[1] = ft_atoi(tokens[2]) - 1;
		indices[2] = ft_atoi(tokens[3]) - 1;
		ft_lstadd(indices_list, ft_lstnew(&indices[0], sizeof(int)));
		ft_lstadd(indices_list, ft_lstnew(&indices[1], sizeof(int)));
		ft_lstadd(indices_list, ft_lstnew(&indices[2], sizeof(int)));
	}
	ft_tabdel(&tokens);
}

static void		set_far_point_dist(char *line, float *far_point)
{
	char	**toks;
	t_vec3	point;
	float	dist;

	if (!(toks = ft_strsplit(line, ' ')))
		error("Model parser error: Invalid tokens !");
	if (toks[0] && ft_strcmp(toks[0], "v") == 0)
	{
		if (!toks[1] || !toks[2] || !toks[3])
			error("Model parser error: Invalid tokens !");
		point = vec3(atof(toks[1]), atof(toks[2]), atof(toks[3]));
		dist = vec3_mag(point);
		if (dist > *far_point)
			*far_point = dist;
	}
}

t_mesh			*model(char *file)
{
	int		fd;
	char	*line;
	t_list	*positions_list;
	t_list	*indices_list;
	float	far_point;

	far_point = 0;
	positions_list = NULL;
	indices_list = NULL;
	fd = open(file, O_RDONLY);
	while (ft_get_next_line(fd, &line) > 0)
	{
		parse_line(line, &positions_list, &indices_list);
		set_far_point_dist(line, &far_point);
		ft_strdel(&line);
	}
	ft_lstrev(&positions_list);
	return (new_mesh(positions_list, indices_list, far_point));
}
