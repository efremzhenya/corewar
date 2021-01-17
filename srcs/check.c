/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:40:06 by lseema            #+#    #+#             */
/*   Updated: 2021/01/16 23:39:22 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		check(t_corewar **corewar)
{
	(*corewar)->checks++;
	die_carrages(corewar, (*corewar)->carrages, NULL, NULL);
	if ((*corewar)->lives >= NBR_LIVE || (*corewar)->checks == MAX_CHECKS)
	{
		(*corewar)->cycles_to_die -= CYCLE_DELTA;
		(*corewar)->checks = 0;
	}
	(*corewar)->lives = 0;
	(*corewar)->last_check_cycle = (*corewar)->cycles;
}

void		die_carrages(t_corewar **corewar, t_carrage *current,
	t_carrage *del, t_carrage *temp)
{
	while (current != NULL)
	{
		if ((*corewar)->cycles_to_die <= 0
			|| ((*corewar)->cycles - current->last_live_cycle) >= (*corewar)->cycles_to_die)
		{
			del = current;
			current = current->next;
			if ((*corewar)->carrages == del)
				(*corewar)->carrages = current;
			else
			{
				temp = (*corewar)->carrages;
				while (temp->next != del)
					temp = temp->next;
				temp->next = temp->next->next;
			}
			free(del);
			(*corewar)->carrages_count--;
		}
		else
			current = current->next;
	}
}
