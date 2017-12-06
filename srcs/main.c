/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:11:00 by hivian            #+#    #+#             */
/*   Updated: 2017/12/06 15:20:41 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>

int					loop_hook(t_env *e)
{
	e->object.rotation_y += 2;
	display(e->object);
	mlx_opengl_swap_buffers(e->win);
	return (0);
}

int					main(int ac, char **av)
{
	t_env			e;

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
	e.object.rotation_y = 0;
	e.object.colors = generate_colors(e.object.face_count * 3);
	display(e.object);
	mlx_opengl_swap_buffers(e.win);
	mlx_hook(e.win, 2, (1L << 0), key_p, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
