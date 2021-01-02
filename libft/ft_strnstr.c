/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:14:39 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:14:39 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	int		pos;

	j = 0;
	i = 0;
	if (s2[0] == '\0')
		return ((char*)&s1[0]);
	pos = -1;
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i] == s2[j] && s1[i] != '\0' && i < len)
		{
			if (pos == -1)
				pos = i;
			i++;
			j++;
		}
		if (s2[j] == '\0')
			return ((char*)&s1[pos]);
		i = (i - j) + 1;
		j = 0;
		pos = -1;
	}
	return (NULL);
}
