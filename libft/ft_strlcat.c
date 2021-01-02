/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:13:50 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:13:50 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t k;
	size_t end_str;

	k = 0;
	while (dst[k] && k < size)
		k++;
	end_str = k;
	if (size)
		while ((k < size - 1) && (src[k - end_str]))
		{
			dst[k] = src[k - end_str];
			k++;
		}
	if (end_str < size)
		dst[k] = '\0';
	k = 0;
	while (src[k])
		k++;
	return (end_str + k);
}
