/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/02 17:12:20 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		init_corewar(t_corewar **corewar)
{
	if (!(*corewar = (t_corewar*)malloc(sizeof(t_corewar))))
		return kill("Error on memory allocating");
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	//и тд
	return (1);
}

void		exec_vm(t_corewar **corewar)
{
	//Старт ВМ
	if (corewar)
	return;
}
