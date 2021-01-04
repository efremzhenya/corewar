/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/04 20:01:34 by lseema           ###   ########.fr       */
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
	(*corewar)->carrage_count = 0;
	set_operations((*corewar)->operations);
	return (1);
}

void		exec_vm(t_corewar **corewar)
{
	init_arena(corewar);
	init_carrages(corewar);
	(*corewar)->winner_id = (*corewar)->carrages->player->id;
	intro_players((*corewar)->players);
	//...
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
