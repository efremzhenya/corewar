/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:46:15 by lseema            #+#    #+#             */
/*   Updated: 2021/01/06 23:01:31 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player		*new_player(int *ac, char **av, t_corewar **corewar, int ind)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	err_allocate(player);
	player->id = 0;
	player->ind = ind;
	if((*corewar)->cw_args->n_pl != -1)
	{
		player->id = (*corewar)->cw_args->n_pl;
		(*corewar)->cw_args->n_pl = -1;
	}
	player->name = ft_strdup(av[*ac]);
	player->comment = "comment";
	player->code = NULL;
	player->size = 0;
	player->next = NULL;
	return (player); 
}

void				add_player(int *ac, char **av, t_corewar **corewar, int ind)
{
	t_player	*tail;
	
	if (ind > MAX_PLAYERS)
		terminate(ERR_1_MAX_PLAYERS);
	if((*corewar)->players == NULL)
		(*corewar)->players = new_player(ac, av, corewar, ind);
	else
	{
		tail = (*corewar)->players;
		while(tail->next)
			tail = tail->next;
		tail->next = new_player(ac, av, corewar, ind);
	}
	(*ac)++;
}