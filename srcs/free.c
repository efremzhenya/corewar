/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:15:05 by lseema            #+#    #+#             */
/*   Updated: 2021/01/30 23:07:19 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_vm(t_corewar **corewar)
{
	if (*corewar)
	{
		if ((*corewar)->players_count)
		{
			free_players(&(*corewar)->players);
			(*corewar)->players_count = 0;
		}
		if ((*corewar)->carrages_count)
		{
			free_carrages(&(*corewar)->carrages);
			(*corewar)->carrages_count = 0;
		}
		if ((*corewar)->cw_args)
			free((*corewar)->cw_args);
		if ((*corewar)->visual)
			free((*corewar)->visual);
		free(*corewar);
	}
}

void	free_players(t_player **players)
{
	t_player	*player;
	t_player	*temp;

	player = *players;
	while (player)
	{
		if (player->code)
			free(player->code);
		if (player->name)
			free(player->name);
		if (player->comment)
			free(player->comment);
		temp = player;
		player = player->next;
		free(temp);
	}
}
