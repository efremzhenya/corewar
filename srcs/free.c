/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:15:05 by lseema            #+#    #+#             */
/*   Updated: 2021/01/04 19:10:55 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_vm(t_corewar **corewar)
{
	if (*corewar)
	{
		//Удаляем игроков, каретки и т.д.
		free(*corewar);
	}
}
