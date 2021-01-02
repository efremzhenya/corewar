/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:15:04 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:15:04 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s || !(new = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len-- > 0)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
