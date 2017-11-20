/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:54:45 by lnieto-m          #+#    #+#             */
/*   Updated: 2015/12/09 20:10:14 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void		*test;

	test = malloc(sizeof(size_t) * size);
	if (test == NULL)
		return (NULL);
	ft_bzero(test, size);
	return (test);
}
