/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:46:15 by lseema            #+#    #+#             */
/*   Updated: 2021/01/05 18:29:13 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player		*new_player(size_t id, char *name, char *comment)
{
	t_player	*player;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (NULL);
	player->id = id;
	player->name = name;
	player->comment = comment;
	player->code = NULL;
	player->size = 0;
	player->next = NULL;
	return (player);
}

int				add_player(t_player **players, t_player *player)
{
	t_player	*tail;

	if (!players || !player)
		return (0);
	tail = *players;
	while (tail->next)
		tail = tail->next;
	tail->next = player;
	return (1);
}

void			free_players(t_player **players)
{
	t_player	*player;
	t_player	*temp;

	player = *players;
	while (player)
	{
		temp = player;
		player = player->next;
		free(temp);
	}
}
