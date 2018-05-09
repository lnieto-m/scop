/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 12:48:35 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/09 15:33:46 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	after_coma(double *result, int index, const char *str)
{
	int indice;

	indice = 10;
	index++;
	while (str[index] <= '9' && str[index] >= '0')
	{
		*result += (double)(str[index] - 48) / indice;
		indice *= 10;
		index++;
	}
}

double		ft_atof(const char *str)
{
	double		result;
	int			index;
	int			tmp;

	result = 0;
	index = 0;
	tmp = index;
	while (str[index] == '\t' || str[index] == ' ' || str[index] == '\n'
			|| str[index] == '\r' || str[index] == '\f' || str[index] == '\v')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		tmp = index;
		index++;
	}
	while (str[index] <= '9' && str[index] >= '0')
	{
		result *= 10;
		result += str[index++] - 48;
	}
	if (str[index] == '.')
		after_coma(&result, index, str);
	if (str[tmp] == '-')
		result *= -1;
	return (result);
}
