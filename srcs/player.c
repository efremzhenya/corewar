/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:46:15 by lseema            #+#    #+#             */
/*   Updated: 2021/02/13 01:08:55 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	*new_player(int *ac, char **av, t_corewar **corewar)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	err_allocate(player);
	player->id = 0;
	if ((*corewar)->cw_args && (*corewar)->cw_args->n_pl != -1)
	{
		if (get_player_by_id(&(*corewar)->players, (*corewar)->cw_args->n_pl))
			terminate(ERR_2_DUP_ID_PLAYER);
		player->id = (*corewar)->cw_args->n_pl;
		(*corewar)->cw_args->n_pl = -1;
	}
	parse_code(av[*ac], &player);
	player->next = NULL;
	return (player);
}

void		add_player(int *ac, char **av, t_corewar **corewar, int ind)
{
	t_player	*tail;

	if (ind > MAX_PLAYERS)
		terminate(ERR_1_MAX_PLAYERS);
	if ((*corewar)->players == NULL)
		(*corewar)->players = new_player(ac, av, corewar);
	else
	{
		tail = (*corewar)->players;
		while (tail->next)
			tail = tail->next;
		tail->next = new_player(ac, av, corewar);
	}
	(*ac)++;
}

void		swap_links(t_link *l, t_player *tmp)
{
	if (l->a->id > l->b->id)
	{
		if (l->a == l->head)
		{
			tmp = l->b->next;
			l->b->next = l->a;
			l->a->next = tmp;
			l->head = l->b;
			l->c = l->b;
		}
		else
		{
			tmp = l->b->next;
			l->b->next = l->a;
			l->a->next = tmp;
			l->c->next = l->b;
			l->c = l->b;
		}
	}
	else
	{
		l->c = l->a;
		l->a = l->a->next;
	}
}

t_player	*sort_players(t_player *head)
{
	t_link	l;

	if (!head)
		return (NULL);
	l.a = NULL;
	l.b = NULL;
	l.c = NULL;
	l.e = NULL;
	l.head = head;
	while (l.e != l.head->next)
	{
		l.a = l.head;
		l.c = l.head;
		l.b = l.a->next;
		while (l.a != l.e)
		{
			swap_links(&l, NULL);
			l.b = l.a->next;
			if (l.b == l.e)
				l.e = l.a;
		}
	}
	return (l.head);
}

t_player	*get_player_by_id(t_player **players, int id)
{
	t_player *player;

	if (players)
	{
		player = *players;
		while (player)
		{
			if (player->id == id)
				return (player);
			player = player->next;
		}
	}
	return (NULL);
}
