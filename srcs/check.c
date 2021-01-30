/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:40:06 by lseema            #+#    #+#             */
/*   Updated: 2021/01/31 01:23:04 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

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
		if ((*corewar)->cycles_to_die <= 0 ||
			((ssize_t)((*corewar)->cycles - current->last_live_cycle))
				>= (*corewar)->cycles_to_die)
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
			if ((*corewar)->cw_args->visual)
			{
				remove_in_set(&(*corewar)->visual->arena[del->pc].set, del);
				(*corewar)->visual->arena[del->pc].update = 1;
			}
			free(del);
			(*corewar)->carrages_count--;
			// if ((*corewar)->cw_args->visual)
			// 	beep();
		}
		else
			current = current->next;
	}
}
