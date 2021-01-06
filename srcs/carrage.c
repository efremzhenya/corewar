/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carrage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:27:32 by lseema            #+#    #+#             */
/*   Updated: 2021/01/06 23:22:29 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carrage		*new_carrage(size_t id, unsigned int pc, t_player *player)
{
	t_carrage	*carrage;
	int			i;

	if (!(carrage = (t_carrage *)malloc(sizeof(t_carrage))))
		return (NULL);
	carrage->id = id;
	carrage->wait_cycles = 0;
	carrage->last_live_cycle = 0;
	carrage->op_code = 0;
	carrage->pc = pc;
	carrage->carry = 0;
	carrage->player = player;
	carrage->next = NULL;
	i = 0;
	while(i < REG_NUMBER)
	{
		carrage->registers[i] = (i == 0) ? -(player->id) : 0;
		i++;
	}
	return (carrage);
}

void		add_carrage(t_carrage **carrages, t_carrage *carrage)
{
	if (carrages && carrage)
	{
		carrage->next = *carrages;
		*carrages = carrage;
	}
}

void		free_carrages(t_carrage **carrages)
{
	t_carrage	*carrage;
	t_carrage	*tmp;

	carrage = *carrages;
	while (carrage)
	{
		tmp = carrage;
		carrage = carrage->next;
		free(tmp);
	}
}

void		init_carrages(t_corewar **corewar)
{
	t_player		*player;
	unsigned int	pc;
	size_t			i;

	player = (*corewar)->players;
	i = 1;
	pc = 0;
	while (player != NULL)
	{
		if (!(*corewar)->carrages)
			(*corewar)->carrages = new_carrage(i, pc, player);
		else
			add_carrage(&(*corewar)->carrages, new_carrage(i, pc, player));
		pc += MEM_SIZE / (*corewar)->players_count;
		player = player->next;
		i++;
	}
	(*corewar)->carrages_count = (*corewar)->players_count;
}
