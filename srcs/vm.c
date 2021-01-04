/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/05 00:57:16 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			init_corewar(t_corewar **corewar)
{
	if (!(*corewar = (t_corewar*)malloc(sizeof(t_corewar))))
		return kill("Error on memory allocating");
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	(*corewar)->cycles = 0;
	(*corewar)->lives = 0;
	(*corewar)->cycles_to_die = CYCLE_TO_DIE;
	(*corewar)->checks = 0;
	(*corewar)->players_count = 0;
	(*corewar)->carrages_count = 0;
	set_operations((*corewar)->operations);
	return (1);
}

void		check(t_corewar **corewar)
{
	t_carrage	*carrage;

	(*corewar)->checks++;
	carrage = (*corewar)->carrages;
	while (carrage != NULL)
	{
		if ((*corewar)->cycles_to_die <= 0
			|| ((*corewar)->cycles - carrage->last_live_cycle) >= (*corewar)->cycles_to_die)
		{
			del_carrage(&(*corewar)->carrages, carrage->id);
			(*corewar)->carrages_count--;
		}
		carrage = carrage->next;
	}

}

void		start_vm(t_corewar **corewar)
{
	init_arena(corewar);
	init_carrages(corewar);
	(*corewar)->champion_id = (*corewar)->carrages->player->id;
	intro_players(&(*corewar)->players);
	while ((*corewar)->carrages_count)
	{
		do_cycle(corewar);
		if ((*corewar)->cycles_to_die <= 0 ||
			((*corewar)->cycles_to_die % (*corewar)->cycles) == 0)
			check(corewar);

	}

}

void		do_cycle(t_corewar **corewar)
{
	t_carrage	*carrage;

	(*corewar)->cycles++;
	carrage = (*corewar)->carrages;
	while (carrage)
	{
		//do operation
		carrage = carrage->next;
	}

}

void		intro_players(t_player **players)
{
	t_player *player;

	if (!players)
		return;
	ft_putendl("Introducing contestants...");
	player = (*players);
	while (player != NULL)
	{
		ft_putstr("* Player ");
		ft_putnbr(player->id);
		ft_putstr(", weighing ");
		ft_putnbr(player->size);
		ft_putstr(" bytes, \"");
		ft_putstr(player->name);
		ft_putstr("\" (\"");
		ft_putstr(player->comment);
		ft_putstr("\") !");
		player = player->next;
	}
}
