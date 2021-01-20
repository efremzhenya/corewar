/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:15:05 by lseema            #+#    #+#             */
/*   Updated: 2021/01/20 21:11:02 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_vm(t_corewar **corewar)
{
	if (*corewar)
	{
		if ((*corewar)->players_count)
		{
			free_players(&(*corewar)->players);
			(*corewar)->players_count = 0;
		}
		if ((*corewar)->carrages_count)
		{
			free_carrages(&(*corewar)->carrages);
			(*corewar)->carrages_count = 0;
		}
		if ((*corewar)->cw_args)
			free((*corewar)->cw_args);
		free(*corewar);
	}
}
