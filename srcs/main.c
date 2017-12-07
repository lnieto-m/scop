/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:11:00 by hivian            #+#    #+#             */
/*   Updated: 2017/12/07 15:22:35 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>

int					loop_hook(t_env *e)
{
	e->object.rotation_y -= 2;
	if (e->object.transition_state != 0
		&& e->object.transition_value != 0
		&& e->object.transition_value != 1)
	{
		if (e->object.transition_state == -1)
			e->object.transition_value -= 0.05;
		else
			e->object.transition_value += 0.05;
		if (e->object.transition_value <= 0.0f
			|| e->object.transition_value >= 1.0f)
			e->object.transition_state = 0;
	}
	display(e->object);
	mlx_opengl_swap_buffers(e->win);
	return (0);
}

GLfloat		*uv_map(int size)
{
	GLfloat	*uv_map;
	int 	i;

	i = 0;
	if (!(uv_map = (GLfloat*)malloc(size * 2 * sizeof(GLfloat))))
		return (NULL);
	while (i < size * 2 && i + 6 < size * 2)
	{
		uv_map[i++] = 0.0f;
		uv_map[i++] = 1.0f;
		uv_map[i++] = 1.0f;
		uv_map[i++] = 0.0f;
		uv_map[i++] = 1.0f;
		uv_map[i++] = 1.0f;
	}
	return (uv_map);
}

int					main(int ac, char **av)
{
	t_env			e;
	int				size_line, endian, bpp, h, w;

	if (ac > 1)
		object_loader(av[1], &e.object);
	printf("faces: %i, vertices: %i\n", e.object.face_count, e.object.vertices_count);
	if (!(e.mlx = mlx_init()))
	{
		ft_putendl("Env error");
		return (-1);
	}
	e.win = mlx_new_opengl_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "scop");
	mlx_opengl_window_set_context(e.win);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	ft_putstr("Renderer: ");
	ft_putendl((char *)renderer);
	ft_putstr("OpenGL version supported: ");
	ft_putendl((char *)version);
	void *xpm_image = mlx_xpm_file_to_image(e.mlx, "bois.xpm", &h, &w);
	e.object.texture = mlx_get_data_addr(xpm_image, &bpp, &size_line, &endian);
	e.object.rotation_y = 0;
	e.object.transition_value = 0.0f;
	e.object.colors = generate_colors(e.object.face_count * 3);
	e.object.uv_map = uv_map(e.object.face_count * 3);
	display(e.object);
	mlx_opengl_swap_buffers(e.win);
	mlx_hook(e.win, 2, (1L << 0), key_p, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
