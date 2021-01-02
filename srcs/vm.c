/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/02 19:50:14 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			init_corewar(t_corewar **corewar)
{
	if (!(*corewar = (t_corewar*)malloc(sizeof(t_corewar))))
		return kill("Error on memory allocating");
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	//и тд
	return (1);
}

void		init_arena(t_corewar **corewar)
{
	int	player_block_size;
	int	player_index;
	int	start_pos;
	int	offset;

	player_block_size = MEM_SIZE / (*corewar)->players_count;
	player_index = 0;
	while (player_index < (*corewar)->players_count)
	{
		start_pos = player_block_size * player_index;
		offset = 0;
		while (offset < (*corewar)->players[player_index].size)
		{
			(*corewar)->arena[start_pos + offset] = (*corewar)->players->code[offset];
			offset++;
		}
		player_index++;
	}
	(*corewar)->winner_id = (*corewar)->players_count - 1;
	(*corewar)->cycles = 0;
	(*corewar)->lives = 0;
	(*corewar)->cycles_to_die = CYCLE_TO_DIE;
	(*corewar)->checks = 0;
}

void		exec_vm(t_corewar **corewar)
{
	init_arena(corewar);
	//...
}
