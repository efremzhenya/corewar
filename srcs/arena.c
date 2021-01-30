/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:06:11 by lseema            #+#    #+#             */
/*   Updated: 2021/01/30 22:43:31 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void				init_arena(t_corewar **corewar)
{
	int				player_block_size;
	int				i;
	int				start_pos;
	unsigned int	offset;
	t_player		*player;

	player_block_size = MEM_SIZE / (*corewar)->players_count;
	i = 0;
	player = (*corewar)->players;
	while (player != NULL)
	{
		start_pos = player_block_size * i;
		offset = 0;
		while (offset < player->size)
		{
			(*corewar)->arena[start_pos + offset] = player->code[offset];
			if ((*corewar)->cw_args->visual)
				(*corewar)->visual->arena[start_pos + offset].code_owner =
					player->id;
			offset++;
		}
		player = player->next;
		i++;
	}
}
