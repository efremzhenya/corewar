/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:09:14 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:09:14 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst_p;
	const unsigned char	*src_p;
	unsigned char		ch;

	dst_p = (unsigned char *)dst;
	src_p = (const unsigned char *)src;
	ch = (unsigned char)c;
	while (n-- > 0)
	{
		if (*src_p == ch)
		{
			*dst_p++ = *src_p;
			return (dst_p);
		}
		*dst_p++ = *src_p++;
	}
	return (NULL);
}
