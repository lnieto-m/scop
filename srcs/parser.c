/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:01:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/09 15:23:50 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	free_splitted_line(char **line, int size)
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

	splitted_line = NULL;
	tab_len = 0;
	if (line == NULL
		|| ft_strcmp(line, "") == 0
		|| (splitted_line = ft_strsplit(line, ' ')) == NULL
		|| ft_strcmp(splitted_line[0], "#") == 0)
	{
		if (splitted_line != NULL)
		{
			while (splitted_line[tab_len] != 0)
				tab_len++;
			free_splitted_line(splitted_line, tab_len);
		}
		return ;
	}
	while (splitted_line[tab_len] != 0)
		tab_len++;
	if (ft_strcmp(splitted_line[0], "v") == 0)
		vertex_parsing(object, vert_i, tab_len, splitted_line);
	else if (ft_strcmp(splitted_line[0], "f") == 0)
		face_parsing(object, face_i, tab_len, splitted_line);
	free_splitted_line(splitted_line, tab_len);
}

static char	**load_file(char *file_name, int *file_size)
{
	int		fd;
	char	**loaded_file;
	char	*line;
	char	**loaded_tmp;

	loaded_file = NULL;
	line = NULL;
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
		if (*file_size == 1)
			loaded_file[*file_size - 1] = ft_strtrim_negative(line);
		else
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
		parse_line(object, object->loaded_file[file_index++],
					&vertices, &faces);
	object->vertices_count = vertices;
	object->face_count = faces;
	printf("Object loaded: %i vertices, %i faces\n", vertices, faces);
	file_index = 0;
	while (file_index < object->file_size)
		free(object->loaded_file[file_index++]);
	free(object->loaded_file);
	return (0);
}
