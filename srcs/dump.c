/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:00:38 by lseema            #+#    #+#             */
/*   Updated: 2021/01/15 22:05:28 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		dump(unsigned char *arena)
{
	int		i;
	int		len;
	char	*hex;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 32))
		{
			ft_putstr(i ? "\n0x" : "0x");
			len = ft_strlen((hex = dec_to_hex(i)));
			while (len++ < 4)
				write(1, "0", 1);
			ft_putstr(hex);
			free(hex);
			write(1, " :", 2);
		}
		write(1, " ", 1);
		hex = dec_to_hex(read_byte(arena, i++));
		write(1, !hex[1] ? "0" : &hex[1], 1);
		write(1, &hex[0], 1);
		free(hex);
	}
	write(1, "\n", 1);
	exit(0);
}

static int		cap(unsigned int n)
{
	unsigned int len;

	len = 1;
	while ((n /= 16))
		len++;
	return (len);
}

char			*dec_to_hex(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	dig;

	len = cap(n);
	if ((str = ft_strnew(len)))
	{
		str[len--] = '\0';
		while (len >= 0)
		{
			dig = n % 16;
			str[len--] = dig + ((dig < 10) ? '0' : 'W');
			n /= 16;
		}
	}
	return (str);
}
