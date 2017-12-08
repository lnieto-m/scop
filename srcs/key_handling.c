/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:41:45 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/07 18:43:33 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			key_p(int keycode, t_env *e)
{
	if (keycode == K_ESC)
	{
		free(e->object.colors);
		free(e->object.uv_map);
		free(e->object.projection_matrix);
		free(e->object.translation_matrix);
		free(e->object.scale_matrix);
		free(e->object.rotation_matrix);
		free(e->object.view_matrix);
		glDeleteProgram(e->shader_programme);
		exit(EXIT_SUCCESS);
	}
	if (keycode == K_T)
	{
		if (e->object.transition_value <= 0)
		{
			e->object.transition_state = 1;
			e->object.transition_value += 0.05f;
		}
		else
		{
			e->object.transition_value -= 0.05f;
			e->object.transition_state = -1;
		}
	}
	if (keycode == K_W)
		e->object.position.z -= 0.25;
	if (keycode == K_S)
		e->object.position.z += 0.25;
	if (keycode == K_D)
		e->object.position.x += 0.25;
	if (keycode == K_A)
		e->object.position.x -= 0.25;
	translation_matrix(e->object.translation_matrix, e->object.position.x,
		e->object.position.y, e->object.position.z);
	display(e->object, e->shader_programme);
	mlx_opengl_swap_buffers(e->win);
	return (0);
}
