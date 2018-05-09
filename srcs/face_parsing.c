/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:12:25 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/09 15:25:52 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	simple_face(t_object *object, int *face_i, int tab_len,
						char **splitted_line)
{
	int		index;
	int		**int_tmp;

	int_tmp = NULL;
	index = 1;
	int_tmp = (int **)realloc(object->faces, sizeof(int *) * (*face_i + 1));
	if (int_tmp != NULL)
		object->faces = int_tmp;
	if (!(object->faces[*face_i] = (int *)malloc(3 * sizeof(int))))
		return ;
	while (index < tab_len)
	{
		object->faces[*face_i][index - 1] = ft_atoi(splitted_line[index]);
		index++;
	}
	*face_i += 1;
}

void		face_parsing(t_object *object, int *face_i, int tab_len,
						char **splitted_line)
{
	int		index;
	int		**int_tmp;

	int_tmp = NULL;
	index = 1;
	if (tab_len > 4)
	{
		int_tmp = (int **)realloc(object->faces, sizeof(int *)
				* (*face_i + tab_len - 3));
		if (int_tmp != NULL)
			object->faces = int_tmp;
		while (index <= tab_len - 3)
		{
			if (!(object->faces[*face_i] = (int *)malloc(3 * sizeof(int))))
				return ;
			object->faces[*face_i][0] = ft_atoi(splitted_line[1]);
			object->faces[*face_i][1] = ft_atoi(splitted_line[index + 1]);
			object->faces[*face_i][2] = ft_atoi(splitted_line[index + 2]);
			index++;
			*face_i += 1;
		}
	}
	else
		simple_face(object, face_i, tab_len, splitted_line);
}
