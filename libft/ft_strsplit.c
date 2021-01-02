/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:14:50 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:14:50 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_words(char const *str, char c)
{
	int i;
	int words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

static int	ft_splitstr(char **arr, const char *s, char d, size_t len)
{
	size_t	j;
	size_t	count;
	size_t	wlen;

	count = 0;
	j = 0;
	while (count < len)
	{
		wlen = 0;
		while (s[j] == d && s[j])
			j++;
		while (s[j] != d && s[j])
		{
			wlen++;
			j++;
		}
		if (!(arr[count] = ft_strsub(&s[j - wlen], 0, wlen)))
			return (0);
		count++;
	}
	arr[count] = NULL;
	return (1);
}

char		**ft_strsplit(char const *str, char c)
{
	size_t	l;
	char	**arr;

	if (!str)
		return (NULL);
	l = ft_num_words(str, c);
	if (!(arr = ((char **)ft_memalloc(sizeof(char *) * (l + 1)))))
		return (NULL);
	if (ft_splitstr(arr, str, c, l))
		return (arr);
	else
		ft_memdel((void **)arr);
	return (arr);
}
