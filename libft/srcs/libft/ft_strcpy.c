/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:28:19 by lnieto-m          #+#    #+#             */
/*   Updated: 2015/11/28 14:27:13 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	if (*src == '\0')
	{
		*dest = *src;
		return (dest);
	}
	else
	{
		*dest = *src;
		ft_strcpy(dest + 1, src + 1);
	}
	return (dest);
}
