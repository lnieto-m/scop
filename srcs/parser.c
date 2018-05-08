/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:01:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/08 12:29:01 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void free_splitted_line(char **line, int size)
{
	int		index;

	index = 0;
	while (index < size)
		free(line[index++]);
	free(line);
}

static void	parse_line(t_object *object, char *line, int *vert_i, int *face_i)
{
	char	**splitted_line;
	int		tab_len;
	int 	i;
	int 	**int_tmp;
	float	**float_tmp;

	int_tmp = NULL;
	float_tmp = NULL;
	splitted_line = NULL;
	i = 1;
	tab_len = 0;
	if (ft_strcmp(line, "") == 0
		|| (splitted_line = ft_strsplit(line, ' ')) == NULL
		|| ft_strcmp(splitted_line[0], "#") == 0/*
		|| ft_strcmp(splitted_line[0], "v") != 0*/)
	{
		if (splitted_line != NULL)
		{
			while (splitted_line[tab_len] != 0)
				tab_len++;
			free_splitted_line(splitted_line, tab_len);
		}
		return;
	}
	printf("%s, %i\n", line, ft_strcmp(splitted_line[0], "#"));
	if (ft_strcmp(splitted_line[0], "v") == 0)
	{
		float_tmp = (float **)realloc(object->vertices, sizeof(float *) * (*vert_i + 1));
		if (float_tmp != NULL)
			object->vertices = float_tmp;
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
			int_tmp = (int **)realloc(object->faces, sizeof(int *) * (*face_i + tab_len - 3));
			if (int_tmp != NULL)
				object->faces = int_tmp;
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
			int_tmp = (int **)realloc(object->faces, sizeof(int *) * (*face_i + 1));
			if (int_tmp != NULL)
				object->faces = int_tmp;
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
	free_splitted_line(splitted_line, tab_len);
}

static char	**load_file(char *file_name, int *file_size)
{
	int		fd;
	char	**loaded_file;
	char	*line;
	char	**loaded_tmp;

	loaded_file = NULL;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		*file_size += 1;
		loaded_tmp = (char **)realloc(loaded_file, *file_size * sizeof(char *));
		if (loaded_tmp != NULL)
			loaded_file = loaded_tmp;
		else
			return (NULL);
		loaded_file = loaded_tmp;
		loaded_file[*file_size - 1] = ft_strdup(line);
		free(line);
	}
	close(fd);
	return (loaded_file);
}

int			object_loader(char *file_name, t_object *object)
{
	int		file_index;
	int		vertices;
	int		faces;

	printf("Loading object...\n");
	file_index = 0;
	faces = 0;
	vertices = 0;
	object->loaded_file = NULL;
	object->file_size = 0;
	object->loaded_file = load_file(file_name, &object->file_size);
	object->faces = NULL;
	object->vertices = NULL;
	while (file_index < object->file_size)
	{
		parse_line(object, object->loaded_file[file_index], &vertices, &faces);
		file_index++;
	}
	object->vertices_count = vertices;
	object->face_count = faces;
	printf("Object loaded: %i vertices, %i faces\n", vertices, faces);
	file_index = 0;
	while (file_index < object->file_size)
		free(object->loaded_file[file_index++]);
	free(object->loaded_file);
	return (0);
}
