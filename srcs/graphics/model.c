/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:53:55 by mploux            #+#    #+#             */
/*   Updated: 2018/01/10 21:19:50 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void		parse_line(
	char *line,
	t_list **positions_list,
	t_list **indices_list)
{
	char	**tokens;
	GLfloat	vertices[3];
	GLuint	indices[3];

	if (!(tokens = ft_strsplit(line, ' ')))
		error("Model parser error: Invalid tokens !");
	if (tokens[0] && ft_strcmp(tokens[0], "v") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");
		vertices[0] = atof(tokens[1]);
		vertices[1] = atof(tokens[2]);
		vertices[2] = atof(tokens[3]);
		ft_lstadd(positions_list, ft_lstnew(&vertices[0], sizeof(GLfloat)));
		ft_lstadd(positions_list, ft_lstnew(&vertices[1], sizeof(GLfloat)));
		ft_lstadd(positions_list, ft_lstnew(&vertices[2], sizeof(GLfloat)));
	}
	else if (tokens[0] && ft_strcmp(tokens[0], "f") == 0)
	{
		if (!tokens[1] || !tokens[2] || !tokens[3])
			error("Model parser error: Invalid tokens !");
		indices[0] = ft_atoi(tokens[1]) - 1;
		indices[1] = ft_atoi(tokens[2]) - 1;
		indices[2] = ft_atoi(tokens[3]) - 1;
		ft_lstadd(indices_list, ft_lstnew(&indices[0], sizeof(GLuint)));
		ft_lstadd(indices_list, ft_lstnew(&indices[1], sizeof(GLuint)));
		ft_lstadd(indices_list, ft_lstnew(&indices[2], sizeof(GLuint)));
	}
	ft_tabdel(&tokens);
}

t_mesh			*new_model(char *file)
{
	int		fd;
	char	*line;
	t_list	*positions_list;
	t_list	*indices_list;

	positions_list = NULL;
	indices_list = NULL;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &positions_list, &indices_list);
		ft_strdel(&line);
	}
	ft_lstrev(&positions_list);
	t_glfloatbuffer vertices = ltfb(positions_list);
	t_gluintbuffer indices = ltib(indices_list);
	return (new_mesh(&vertices, &indices));
}
