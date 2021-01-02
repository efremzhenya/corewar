/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:15:09 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:15:09 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	end;
	char	*dst;

	if (!s)
		return (NULL);
	while ((*s == ' ') || (*s == '\n') || (*s == '\t'))
		s++;
	if (!(end = ft_strlen(s)))
		return (ft_strnew(0));
	end = end - 1;
	while (((s[end] == ' ') || (s[end] == '\n') || (s[end] == '\t')))
		end--;
	if (!(dst = ft_strnew(end)))
		return (NULL);
	i = 0;
	while (i <= end)
		dst[i++] = *s++;
	dst[i] = '\0';
	return (dst);
}
