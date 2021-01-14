/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carrage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:27:32 by lseema            #+#    #+#             */
/*   Updated: 2021/01/14 22:11:40 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carrage		*new_carrage(unsigned int pc, t_player *player)
{
	t_carrage	*carrage;
	int			i;

	if (!(carrage = (t_carrage *)malloc(sizeof(t_carrage))))
		return (NULL);
	carrage->wait_cycles = 0;
	carrage->last_live_cycle = 0;
	carrage->op_code = 0;
	carrage->is_half_size_dir = 0;
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

	player = (*corewar)->players;
	pc = 0;
	while (player != NULL)
	{
		if (!(*corewar)->carrages)
			(*corewar)->carrages = new_carrage(pc, player);
		else
			add_carrage(&(*corewar)->carrages, new_carrage(pc - 1, player));
		pc += MEM_SIZE / (*corewar)->players_count;
		player = player->next;
	}
	(*corewar)->carrages_count = (*corewar)->players_count;
}
