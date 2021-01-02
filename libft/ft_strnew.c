/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:14:35 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:14:35 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!(p = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while ((i <= size))
	{
		*(p + i) = '\0';
		i++;
	}
	return (p);
}
