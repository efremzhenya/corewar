/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:06:59 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:06:59 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cap(int n, int minus)
{
	int len;

	len = 1;
	while ((n /= 10))
		len++;
	return (minus + len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		znak;
	int		dig;

	znak = (n < 0) ? 1 : 0;
	len = cap(n, znak);
	if ((str = ft_strnew(len)))
	{
		str[len--] = '\0';
		while (len >= znak)
		{
			dig = n % 10;
			str[len--] = (dig < 0 ? dig * -1 : dig) + '0';
			n /= 10;
		}
		if (znak)
			str[0] = '-';
	}
	return (str);
}
