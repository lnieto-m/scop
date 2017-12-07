/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:30:43 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/07 14:27:54 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat		*rotation_y_matrix(float angle)
{
	GLfloat *matrix;

	if (!(matrix = (GLfloat*)malloc(16 * sizeof(GLfloat))))
		return (NULL);
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	matrix[0] = cos(angle * M_PI / 180);
	matrix[2] = sin(angle * M_PI / 180);
	matrix[5] = 1.0f;
	matrix[8] = -1 * sin(angle * M_PI / 180);
	matrix[10] = cos(angle * M_PI / 180);
	matrix[15] = 1.0f;
	return (matrix);
}

GLfloat		*projection_matrix(float fov, float near, float far, float aspect)
{
	float	scale;
	GLfloat *matrix;

	scale = 1.0f / (tan(fov / 2.0f * M_PI / 180.0f));
	if (!(matrix = (GLfloat*)malloc(16 * sizeof(GLfloat))))
		return (NULL);
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	(void)aspect;
	matrix[0] = scale;
	matrix[5] = scale * aspect;
	matrix[10] = -1 * (far + near) / (far - near);
	matrix[11] = -2 * (far * near) / (far - near);
	matrix[14] = -1.0f;
	return (matrix);
}

void		normalize(t_vector *v)
{
	float	dist;

	dist = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= dist;
	v->y /= dist;
	v->z /= dist;
}

GLfloat		*view_matrix(void)
{
	t_vector eye;
	t_vector center;
	t_vector up;
	t_vector forward;
	t_vector side;

	center.x = 0.0f;
	center.y = 0.0f;
	center.z = 0.0f;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	eye.x = 4.0f;
	eye.y = 3.0f;
	eye.z = 3.0f;
	forward.x = center.x - eye.x;
	forward.y = center.y - eye.y;
	forward.z = center.z - eye.z;
	side.x = forward.x * up.x;
	side.y = forward.y * up.y;
	side.z = forward.y * up.z;
	normalize(&side);
	up.x = side.x * forward.x;
	up.y = side.y * forward.y;
	up.z = side.z * forward.z;
	GLfloat	*matrix;
	if (!(matrix = (GLfloat*)malloc(16 * sizeof(GLfloat))))
		return (NULL);
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	matrix[0] = side.x;
	matrix[4] = side.y;
	matrix[8] = side.z;
	matrix[12] = 0.0f;
	matrix[1] = up.x;
	matrix[5] = up.y;
	matrix[9] = up.z;
	matrix[13] = 0.0f;
	matrix[2] = -1 * forward.x;
	matrix[6] = -1 * forward.y;
	matrix[10] = -1 * forward.z;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
	matrix[3] = 0.0f - eye.x;
	matrix[7] = 0.0f - eye.y;
	matrix[11] = 0.0f - eye.z;
	// int i = 0;
	// while (i < 16)
	// 	printf("%f\n", matrix[i++]);
	// printf("\n");
	return (matrix);
}
