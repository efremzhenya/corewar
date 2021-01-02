/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:09:37 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:09:37 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*src_p;
	unsigned char		*dst_p;

	if ((!dst) && (!src))
		return (dst);
	src_p = src;
	dst_p = dst;
	while (n-- > 0)
		*dst_p++ = *src_p++;
	return (dst);
}
