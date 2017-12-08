/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:33:45 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/08 11:16:47 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		create_matrices(t_object *obj)
{
	obj->projection_matrix = create_matrix(16);
	obj->translation_matrix = create_matrix(16);
	obj->scale_matrix = create_matrix(16);
	obj->rotation_matrix = create_matrix(16);
	obj->view_matrix = create_matrix(16);
}

void		load_texture(t_env *e)
{
	void	*xpm_image;
	int		bpp;
	int		size_line;
	int		endian;

	xpm_image = mlx_xpm_file_to_image(e->mlx, "bois.xpm", &bpp, &size_line);
	e->object.texture = mlx_get_data_addr(xpm_image, &bpp, &size_line, &endian);
}

void		load_points(t_object *obj, int size)
{
	int			f_i;
	int			p_i;
	int			l_i;

	f_i = 0;
	l_i = 0;
	p_i = 0;
	if (!(obj->points = (float*)malloc(size * 3 * sizeof(float))))
		return ;
	while (l_i < obj->face_count)
	{
		while (f_i < 3)
		{
			obj->points[p_i++] = obj->vertices[obj->faces[l_i][f_i] - 1][0];
			obj->points[p_i++] = obj->vertices[obj->faces[l_i][f_i] - 1][1];
			obj->points[p_i++] = obj->vertices[obj->faces[l_i][f_i++] - 1][2];
		}
		f_i = 0;
		l_i++;
	}
}

void		init_object(t_object *obj, char *filename)
{
	object_loader(filename, obj);
	obj->rotation_y = 0;
	obj->transition_value = 1.0f;
	obj->colors = generate_colors(obj->face_count * 3);
	obj->uv_map = uv_map(obj->face_count * 3);
	create_matrices(obj);
	load_points(obj, obj->face_count * 3);
	obj->position.x = 0;
	obj->position.y = 0;
	obj->position.z = -3.0;
	rotation_y_matrix(obj->rotation_matrix, 0);
	scale_matrix(obj->scale_matrix, 0.3, 0.3, 0.3);
	translation_matrix(obj->translation_matrix, obj->position.x,
		obj->position.y, obj->position.z);
	projection_matrix(obj->projection_matrix, 45.0f,
		(float)(WIN_WIDTH / WIN_HEIGHT));
	translation_matrix(obj->view_matrix, 0, 0, 0);
}
