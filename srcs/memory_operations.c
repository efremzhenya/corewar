/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:01:20 by lseema            #+#    #+#             */
/*   Updated: 2021/02/13 21:34:10 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

unsigned char	read_byte(unsigned char *arena, int pos)
{
	return (arena[normalize_pc(pos)]);
}

short			read_int16(unsigned char *arena, int pos)
{
	unsigned long	i;
	short			bytes[sizeof(short)];

	i = 0;
	while (i < (sizeof(short)))
	{
		bytes[i] = read_byte(arena, pos + i);
		i++;
	}
	return ((bytes[0] << 8) | bytes[1]);
}

int				read_int32(unsigned char *arena, int pos)
{
	unsigned long	i;
	int				bytes[sizeof(int)];

	i = 0;
	while (i < (int)sizeof(int))
	{
		bytes[i] = read_byte(arena, pos + i);
		i++;
	}
	return ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
}

void			write_byte(t_corewar **corewar, int pos, unsigned char byte)
{
	(*corewar)->arena[pos = normalize_pc(pos)] = byte;
}

void			write_int32(t_corewar **corewar, int pos, int value, int owner)
{
	unsigned long	i;
	unsigned char	byte;

	i = 0;

	pos = normalize_pc(pos);
	while (i < sizeof(int))
	{
		byte = (value >> (((sizeof(int) - (i + 1)) * 8))) & 0b11111111;
		write_byte(corewar, normalize_pc(pos + i), byte);
		if ((*corewar)->cw_args->visual)
		{
			(*corewar)->visual->arena[normalize_pc(pos + i)].code_owner = owner;
			(*corewar)->visual->arena[normalize_pc(pos + i)].update = 1;
		}
		i++;
	}
}
