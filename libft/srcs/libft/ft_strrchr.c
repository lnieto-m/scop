/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:14:46 by lnieto-m          #+#    #+#             */
/*   Updated: 2015/11/28 22:17:58 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (*s)
		s++;
	if (c == 0)
		return ((char *)s);
	else
	{
		while (i >= 0)
		{
			if (*s == c)
				return ((char *)s);
			s--;
			i--;
		}
	}
	return (NULL);
}
