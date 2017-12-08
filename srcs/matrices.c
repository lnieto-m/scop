/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:30:43 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/08 10:49:20 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Matrix order
** [0][4][ 8][12]
** [1][5][ 9][13]
** [2][6][10][14]
** [3][7][11][15]
*/

GLfloat 	*create_matrix(int size)
{
	GLfloat		*matrix;

	if (!(matrix = (GLfloat*)malloc(size * sizeof(GLfloat))))
		return (NULL);
	ft_bzero(matrix, size * sizeof(GLfloat));
	return (matrix);
}

void		rotation_y_matrix(GLfloat *matrix, float angle)
{
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	matrix[0] = cos(angle * M_PI / 180);
	matrix[2] = -1 * sin(angle * M_PI / 180);
	matrix[5] = 1.0f;
	matrix[8] = sin(angle * M_PI / 180);
	matrix[10] = cos(angle * M_PI / 180);
	matrix[15] = 1.0f;
}

void		projection_matrix(GLfloat *matrix, float fov, float aspect)
{
	float	scale;

	scale = 1.0f / (tan(fov / 2.0f * M_PI / 180.0f));
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	matrix[0] = scale * aspect;
	matrix[5] = scale;
	matrix[10] = -1.0f * (100.0f + 0.1f) / (100.0f - 0.1f);
	matrix[11] = -1.0f;
	matrix[14] = -2.0f * (100.0f * 0.1f) / (100.0f - 0.1f);
}

void		translation_matrix(GLfloat *matrix, float x, float y, float z)
{
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	matrix[0] = 1.0f;
	matrix[3] = x;
	matrix[5] = 1.0f;
	matrix[7] = y;
	matrix[10] = 1.0f;
	matrix[11] = z;
	matrix[15] = 1.0f;
}

void		scale_matrix(GLfloat *matrix, float x, float y, float z)
{
	ft_bzero(matrix, 16 * sizeof(GLfloat));
	matrix[0] = x;
	matrix[5] = y;
	matrix[10] = z;
	matrix[15] = 1.0f;
}
