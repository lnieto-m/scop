/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:30:43 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/02 15:01:35 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	rotation(float *point, t_vector vector)
{
	t_vector	tmp_point;
	t_vector	sinus;

	if (vector.x || vector.y || vector.z)
	{
		sinus.x = sin(vector.x);
		sinus.y = sin(vector.y);
		sinus.z = sin(vector.z);
		vector.x = cos(vector.x);
		vector.y = cos(vector.y);
		vector.z = cos(vector.z);
		tmp_point.x = point[0];
		tmp_point.y = point[1];
		tmp_point.z = point[2];
		point[0] = tmp_point.x * vector.y * vector.z - tmp_point.y * vector.y * sinus.z + tmp_point.z * sinus.y;
		point[1] = tmp_point.x * (vector.x * sinus.z + sinus.x * sinus.y * vector.z) + tmp_point.y *
			(vector.x * vector.z - sinus.x * sinus.y * sinus.z) - tmp_point.z * sinus.x *
			vector.y;
		point[2] = tmp_point.x * (sinus.x * sinus.z - vector.x * sinus.y *vector.z) + tmp_point.y *
			(sinus.x * vector.z + vector.x * sinus.y * sinus.z) + tmp_point.z * vector.x *
			vector.y;
	}
}
