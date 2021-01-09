/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:46:15 by lseema            #+#    #+#             */
/*   Updated: 2021/01/08 23:38:59 by mellie           ###   ########.fr       */
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

t_player	*sort_players(t_player *tmp, t_player *head)
{
 	t_player *a = NULL;
 	t_player *b = NULL; 
 	t_player *c = NULL;
 	t_player *e = NULL; 

	while (e != head->next)
	{
		a = head;
		c = head;
		b = a->next;
		while (a != e)
		{
			if (a->id > b->id)
			{
				if (a == head)
				{
					tmp = b -> next;
					b->next = a;
					a->next = tmp;
					head = b;
					c = b;
				}
				else
				{
					tmp = b->next;
					b->next = a;
					a->next = tmp;
					c->next = b;
					c = b;
				}
			}
			else
			{
				c = a;
				a = a->next;
			}
			b = a->next;
			if (b == e)
				e = a;
		}
	}
	return (head);
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
