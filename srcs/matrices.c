/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:30:43 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/06 14:32:56 by lnieto-m         ###   ########.fr       */
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
	matrix[5] = scale;
	matrix[10] = -1 * (far + near) / (far - near);
	matrix[11] = -2 * far * near / (far - near);
	matrix[14] = -1.0f;
	int i = 0;
	while (i < 16)
		printf("%f\n", matrix[i++]);
	return (matrix);
}

GLfloat		*view_matrix()
{
	GLfloat	*matrix;
	if (!(matrix = (GLfloat*)malloc(16 * sizeof(GLfloat))))
		return (NULL);
	ft_bzero(matrix, 16 * sizeof(GLfloat));

	return (matrix);
}
