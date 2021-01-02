/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:10:03 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:10:03 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if ((!dst) && (!src))
		return (dst);
	if (src >= dst)
		while (len--)
			*p_dst++ = *p_src++;
	else
	{
		p_dst = p_dst + len - 1;
		p_src = p_src + len - 1;
		while (len--)
			*p_dst-- = *p_src--;
	}
	return (dst);
}
