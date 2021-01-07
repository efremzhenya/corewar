/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:01:20 by lseema            #+#    #+#             */
/*   Updated: 2021/01/08 00:11:53 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	read_byte(unsigned char *arena, unsigned int pos)
{
	while (pos >= MEM_SIZE)
		pos = pos - MEM_SIZE;
	// while (pos < 0)
	// 	pos = MEM_SIZE + pos;
	return arena[pos];
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
	while (pos >= MEM_SIZE)
		pos = pos - MEM_SIZE;
	(*corewar)->arena[pos] = byte;
}

void			write_int32(t_corewar **corewar, int pos, int value)
{
	unsigned long	i;
	unsigned char	byte;

	i = 0;
	while (i < sizeof(int))
	{
		byte = value >> ((sizeof(int) - (i + 1) * 8)) | 0xff;
		write_byte(corewar, pos + i++, byte);
	}
}
