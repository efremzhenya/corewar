/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:46:15 by lseema            #+#    #+#             */
/*   Updated: 2021/01/09 21:14:27 by mellie           ###   ########.fr       */
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
	if ((*corewar)->cw_args->n_pl != -1)
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
	if ((*corewar)->players == NULL)
		(*corewar)->players = new_player(ac, av, corewar, ind);
	else
	{
		tail = (*corewar)->players;
		while (tail->next)
			tail = tail->next;
		tail->next = new_player(ac, av, corewar, ind);
	}
	(*ac)++;
}

void			fill_player_id(t_corewar **corewar)
{
	t_player	*tmp;
	t_player	*tmp2;
	int			j;

	tmp = (*corewar)->players;
	while (tmp)
	{
		if (tmp->id == 0)
		{
			j = tmp->ind;
			tmp2 = (*corewar)->players;
			while (tmp2 && j <= (*corewar)->players_count)
			{
				if (tmp2->id == j)
				{
					j++;
					tmp2 = (*corewar)->players;
				}
				else
					tmp2 = tmp2->next;
			}
			tmp->id = j;
		}
			tmp = tmp->next;
	}
}

void		init_links(t_link **l, t_player *head)
{
		(*l)->a = NULL;
		(*l)->b = NULL;
		(*l)->c = NULL;
		(*l)->e = NULL;
		(*l)->head = head;
}

void		swap_links(t_link *l, t_player	*tmp)
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

	l.a = NULL;
	l.b = NULL;
	l.c = NULL;
	l.e = NULL;
	l.head = head;	
//	init_links(&l, head);
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

t_player		*get_player_by_id(t_player **players, int id)
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
