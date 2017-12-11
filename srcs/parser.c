/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:01:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/11 14:19:18 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	parse_line(t_object *object, char *line, int *vert_i, int *face_i)
{
	char	**splitted_line;
	int		tab_len;
	int 	i;

	i = 1;
	tab_len = 0;
	if (ft_strcmp(line, "") == 0
		|| (splitted_line = ft_strsplit(line, ' ')) == NULL
		|| ft_strcmp(splitted_line[0], "#") == 0)
		return;
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
		if (tab_len > 4)
		{
			int index = 1;
			while (index <= tab_len - 3)
			{
				if(!(object->faces[*face_i] = (int *)malloc(3 * sizeof(int))))
					return;
				object->faces[*face_i][0] = ft_atoi(splitted_line[1]);
				object->faces[*face_i][1] = ft_atoi(splitted_line[index + 1]);
				object->faces[*face_i][2] = ft_atoi(splitted_line[index + 2]);
				index++;
				*face_i += 1;
			}
		} else {
			if(!(object->faces[*face_i] = (int *)malloc(3 * sizeof(int))))
				return;
			while (i < tab_len)
			{
				object->faces[*face_i][i - 1] = ft_atoi(splitted_line[i]);
				i++;
			}
			*face_i += 1;
		}
	}
}

static int	count_vertex(char *file_name, int *face_count, int *vertices_count)
{
	char	**splitted_line;
	int		fd;
	char	*line;
	int		err;
	int		tab_len;

	tab_len = 0;
	fd = open(file_name, O_RDONLY);
	while ((err = get_next_line(fd, &line)) > 0)
	{
		if (err == -1)
			return (err);
		if (ft_strcmp(line, "") == 0
			|| (splitted_line = ft_strsplit(line, ' ')) == NULL
			|| ft_strcmp(splitted_line[0], "#") == 0)
			continue;
		if (ft_strcmp(splitted_line[0], "v") == 0)
			*vertices_count += 1;
		else if (ft_strcmp(splitted_line[0], "f") == 0)
		{
			while (splitted_line[tab_len] != 0)
				tab_len++;
			*face_count += tab_len - 3;
		}
		free(line);
		tab_len = 0;
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

	printf("Loading object...\n");
	err = 0;
	faces = 0;
	vertices = 0;
	count_vertex(file_name, &faces, &vertices);
	if (!(object->faces = (int**)malloc(faces * sizeof(int*))))
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
	printf("Object loaded: %i vertices, %i faces\n", vertices, faces);
	return (0);
}
