/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:41:45 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/07 15:20:36 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			key_p(int keycode, t_env *e)
{
	if (keycode == K_ESC)
	{
		free(e->object.colors);
		free(e->object.uv_map);
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
	display(e->object);
	mlx_opengl_swap_buffers(e->win);
	return (0);
}
