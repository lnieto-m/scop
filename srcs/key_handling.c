/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:41:45 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/06 15:31:49 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			key_p(int keycode, t_env *e)
{
	if (keycode == K_ESC)
	{
		free(e->object.colors);
		exit(EXIT_SUCCESS);
	}
	display(e->object);
	mlx_opengl_swap_buffers(e->win);
	return (0);
}
