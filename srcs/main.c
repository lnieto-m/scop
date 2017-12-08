/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:11:00 by hivian            #+#    #+#             */
/*   Updated: 2017/12/07 18:40:19 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int					loop_hook(t_env *e)
{
	e->object.rotation_y += 2;
	if (e->object.rotation_y >= 360.0f)
		e->object.rotation_y = 0;
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
	rotation_y_matrix(e->object.rotation_matrix, e->object.rotation_y);
	display(e->object, e->shader_programme);
	mlx_opengl_swap_buffers(e->win);
	return (0);
}

GLfloat				*uv_map(int size)
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

	if (ac > 1)
		init_object(&e.object, av[1]);
	if (!(e.mlx = mlx_init()))
	{
		ft_putendl("Env error");
		return (-1);
	}
	e.win = mlx_new_opengl_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "scop");
	mlx_opengl_window_set_context(e.win);
	printf("Renderer: %s\nOpenGL version supported: %s\n",
		glGetString(GL_RENDERER), glGetString(GL_VERSION));
	load_texture(&e);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	e.shader_programme = create_shader();
	display(e.object, e.shader_programme);
	mlx_opengl_swap_buffers(e.win);
	mlx_hook(e.win, 2, (1L << 0), key_p, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
