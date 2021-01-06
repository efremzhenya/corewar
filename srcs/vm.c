/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/04 21:13:02 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		init_corewar(t_corewar **corewar)
{
	if (!(*corewar = (t_corewar*)malloc(sizeof(t_corewar))))
		return kill("Error on memory allocating");
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	(*corewar)->cw_args = NULL;
	//и тд
	return (1);
}

void		exec_vm(t_corewar **corewar)
{
	//Старт ВМ
	if (corewar)
	return;
}
