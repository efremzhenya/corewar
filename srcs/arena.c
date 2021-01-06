/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:06:11 by lseema            #+#    #+#             */
/*   Updated: 2021/01/06 22:25:19 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_arena(t_corewar **corewar)
{
	int			player_block_size;
	int			i;
	int			start_pos;
	int			offset;
	t_player	*player;

	player_block_size = MEM_SIZE / (*corewar)->players_count;
	i = 0;
	player = (*corewar)->players;
	while (player != NULL)
	{
		start_pos = player_block_size * i - (!!i);
		offset = 0;
		while (offset < player->size)
		{
			(*corewar)->arena[start_pos + offset] = player->code[offset];
			offset++;
		}
		player = player->next;
		i++;
	}
}
