/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carrage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:27:32 by lseema            #+#    #+#             */
/*   Updated: 2021/01/30 22:43:07 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

t_carrage	*new_carrage(t_corewar **corewar, unsigned int pc, t_player *player,
	int is_dup)
{
	t_carrage	*carrage;

	if (!(carrage = (t_carrage *)malloc(sizeof(t_carrage))))
		err_allocate(carrage);
	carrage->wait_cycles = 0;
	carrage->last_live_cycle = 0;
	carrage->op_code = 0;
	carrage->is_half_size_dir = 0;
	carrage->pc = pc;
	carrage->carry = 0;
	carrage->player = player;
	carrage->next = NULL;
	ft_bzero(carrage->registers, sizeof(carrage->registers));
	if (!is_dup)
		carrage->registers[0] = -(player->id);
	if ((*corewar)->cw_args->visual)
	{
		add_to_set(&(*corewar)->visual->arena[carrage->pc].set,
			new_set_elem(carrage));
		(*corewar)->visual->arena[pc].update = 1;
	}
	return (carrage);
}

void		add_carrage(t_carrage **carrages, t_carrage *carrage)
{
	if (carrages && carrage)
	{
		if (*carrages)
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
			(*corewar)->carrages = new_carrage(corewar, pc, player, 0);
		else
			add_carrage(&(*corewar)->carrages, new_carrage(corewar, pc, player, 0));
		pc += MEM_SIZE / (*corewar)->players_count;
		player = player->next;
	}
	(*corewar)->carrages_count = (*corewar)->players_count;
}
