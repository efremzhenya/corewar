/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:41:47 by lseema            #+#    #+#             */
/*   Updated: 2021/01/16 23:39:42 by mellie           ###   ########.fr       */
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
		ft_putendl("\") !");
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
			ft_putendl(") won");
			break;
		}
		else
			player = player->next;
	}
}
