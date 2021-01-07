/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:41:47 by lseema            #+#    #+#             */
/*   Updated: 2021/01/08 00:09:49 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		intro_message(t_player **players)
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
		ft_putstr("\") !\n");
		player = player->next;
	}
}

void		alive_message(t_player *player)
{
	ft_putstr("A process shows that player ");
	ft_putnbr(player->id);
	ft_putstr(" (");
	ft_putstr(player->name);
	ft_putstr(") is alive\n");
}

void		winner_message(t_corewar **corewar)
{
	t_player *player;

	player = (*corewar)->players;
	while (player)
	{
		if (player->id == (*corewar)->winner)
		{
			ft_putstr("Player ");
			ft_putnbr(player->id);
			ft_putstr(" (");
			ft_putstr(player->name);
			ft_putstr(") won\n");
			break;
		}
		else
			player = player->next;
	}
}
