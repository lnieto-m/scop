/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_negative.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:08:46 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/09 13:02:07 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_negative(char const *s)
{
	char	*new_str;
	int		i;
	int		j;
	int		n;

	n = 0;
	i = 0;
	if (!s || ft_strcmp(s, "") == 0)
		return (ft_strdup("\0"));
	j = ft_strlen(s) - 1;
	while (s[i] < 0 || s[i] == 32 || s[i] == 10 || s[i] == '\t' || s[i] > 126)
		i++;
	while ((s[j] < 0 || s[j] == 32 || s[j] == 10 || s[j] == '\t' || s[j] > 126)
		&& j > 0)
		j--;
	new_str = (char *)malloc(sizeof(char) * (j - i));
	if (new_str == NULL)
		return (NULL);
	if (j > i)
	{
		while (i <= j)
			new_str[n++] = s[i++];
	}
	new_str[n] = '\0';
	return (new_str);
}
