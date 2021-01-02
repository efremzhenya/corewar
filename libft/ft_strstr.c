/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:14:59 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:14:59 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;
	long int	pos;

	j = 0;
	i = 0;
	if (needle[0] == '\0')
		return ((char*)&haystack[0]);
	pos = -1;
	while (haystack[i] != '\0' && needle[j] != '\0')
	{
		while (haystack[i] == needle[j] && haystack[i] != '\0')
		{
			if (pos == -1)
				pos = i;
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char*)&haystack[pos]);
		i = (i - j) + 1;
		j = 0;
		pos = -1;
	}
	return (NULL);
}
