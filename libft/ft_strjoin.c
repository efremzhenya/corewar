/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:13:45 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:13:45 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	char	*res;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s2[k] != '\0')
		k++;
	if (!(res = (char*)malloc(sizeof(char) * (k + i) + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		res[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		res[k++] = s2[i++];
	res[k] = '\0';
	return (res);
}
