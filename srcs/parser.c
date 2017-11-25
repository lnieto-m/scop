/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:01:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/11/25 11:50:51 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>

static void	parse_line(t_object *object, char *line, int *vert_i, int *face_i)
{
	char	**splitted_line;
	int		tab_len;
	int 	i;

	i = 0;
	tab_len = 0;
	if ((splitted_line = ft_strsplit(line, ' ')) == NULL
		|| ft_strcmp(splitted_line[0], "#") == 0)
		return;
	printf("parser.c line 27: line : %s, vert: %i, face: %i\n", line, *vert_i, *face_i);
	if (ft_strcmp(splitted_line[0], "v") == 0)
	{
		while (splitted_line[tab_len] != 0)
			tab_len++;
		if(!(object->vertices[*vert_i] = (float *)malloc(4 * sizeof(float))))
			return;
		object->vertices[*vert_i][0] = ft_atof(splitted_line[1]);
		object->vertices[*vert_i][1] = ft_atof(splitted_line[2]);
		object->vertices[*vert_i][2] = ft_atof(splitted_line[3]);
		if (tab_len == 5)
			object->vertices[*vert_i][3] = ft_atof(splitted_line[4]);
		else
			object->vertices[*vert_i][3] = 1.0f;
		*vert_i += 1;
	}
	else if (ft_strcmp(splitted_line[0], "f") == 0)
	{
		while (splitted_line[tab_len] != 0)
			tab_len++;
		printf("parser.c line 47: tab_len: %i\n", tab_len);
		if(!(object->faces[*face_i] = (float *)malloc(tab_len * sizeof(float))))
		 	return;
		while (i < tab_len - 1)
		{
			object->faces[*face_i][i] = ft_atof(splitted_line[i + 1]);
			i++;
		}
		*face_i += 1;
	}
	printf("parser.c line 56: line : %s, vert: %i, face: %i\n", line, *vert_i, *face_i);
}

static int	count_vertex(char *file_name, int *face_count, int *vertices_count)
{
	char	**splitted_line;
	int		fd;
	char	*line;
	int		err;

	fd = open(file_name, O_RDONLY);
	while ((err = get_next_line(fd, &line)) > 0)
	{
		if (err == -1)
			return (err);
		if ((splitted_line = ft_strsplit(line, ' ')) == NULL
			|| ft_strcmp(splitted_line[0], "#") == 0)
			continue;
		if (ft_strcmp(splitted_line[0], "v") == 0)
			*vertices_count += 1;
		else if (ft_strcmp(splitted_line[0], "f") == 0)
			*face_count += 1;
		free(line);
	}
	close(fd);
	return (0);
}

int			object_loader(char *file_name, t_object *object)
{
	int		fd;
	int		err;
	char	*line;
	int		vertices;
	int		faces;

	err = 0;
	count_vertex(file_name, &vertices, &faces);
	printf("parser.c line 92: v: %i, f: %i\n", vertices, faces);
	if (!(object->faces = (float**)malloc(faces * sizeof(float*))))
		return (-1);
	if (!(object->vertices = (float**)malloc(vertices * sizeof(float*))))
		return (-1);
	object->vertices_count = vertices;
	object->face_count = faces;
	fd = open(file_name, O_RDONLY);
	vertices = 0;
	faces = 0;
	while ((err = get_next_line(fd, &line)) > 0)
	{
		if (err == -1)
			return (err);
		parse_line(object, line, &vertices, &faces);
		free(line);
	}
	err = close(fd);
	printf("err: %i\n", err);
	return (0);
}
