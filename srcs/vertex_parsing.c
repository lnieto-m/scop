/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:17:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/09 15:26:02 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	vertex_parsing(t_object *object, int *vert_i, int tab_len,
						char **splitted_line)
{
	float	**float_tmp;

	float_tmp = NULL;
	float_tmp = (float **)realloc(object->vertices, sizeof(float *)
				* (*vert_i + 1));
	if (float_tmp != NULL)
		object->vertices = float_tmp;
	if (!(object->vertices[*vert_i] = (float *)malloc(4 * sizeof(float))))
		return ;
	object->vertices[*vert_i][0] = ft_atof(splitted_line[1]);
	object->vertices[*vert_i][1] = ft_atof(splitted_line[2]);
	object->vertices[*vert_i][2] = ft_atof(splitted_line[3]);
	if (tab_len == 5)
		object->vertices[*vert_i][3] = ft_atof(splitted_line[4]);
	else
		object->vertices[*vert_i][3] = 1.0f;
	*vert_i += 1;
}
