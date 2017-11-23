/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:01:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/11/23 11:53:52 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	parse_line(t_object *object, char *line)
{
	char	**splitted_line;

	if ((splitted_line = ft_strsplit(line, ' ')) == NULL
		|| ft_strcmp(splitted_line[0], "#") == 0)
		return;

}

int			object_loader(char *file_name, t_object *object)
{
	int		fd;
	int		err;
	char	*line;

	err = 0;
	fd = open(file_name, O_RDONLY);
	while ((err = get_next_line(fd, &line)) > 0)
	{
		if (err == -1)
			return (err);
		parse_line(object, line);
		free(str);
	}
	close(fd);
	return (0)
}
