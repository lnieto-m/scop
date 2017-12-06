/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:55:48 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/06 15:22:33 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

double		frand_a_b(double a, double b){
	return ((rand() / (double)RAND_MAX) *(b - a) + a);
}

float		*generate_colors(int obj_size)
{
	float	*colors;
	double	face_color;
	int		i;
	int		j;

	face_color = 0;
	i = 0;
	j = 0;
	if (!(colors = (float*)malloc(obj_size * 3 * sizeof(float))))
		return (NULL);
	while (i < obj_size * 3)
	{
		face_color = frand_a_b(0.2, 0.7);
		j = i + 9;
		while (i < j && i < obj_size * 3)
			colors[i++] = face_color;
	}
	return (colors);
}
