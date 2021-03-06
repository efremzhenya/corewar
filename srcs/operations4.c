/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:15:06 by lseema            #+#    #+#             */
/*   Updated: 2021/01/21 21:50:46 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_aff(t_corewar **corewar, t_carrage *carrage)
{
	int reg_value;
	int offset;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	reg_value = carrage->registers[read_byte((*corewar)->arena, offset)];
	ft_putstr("Aff: ");
	ft_putchar((char)reg_value % 256);
	ft_putstr("\n");
}

void	op_nop(t_corewar **corewar, t_carrage *carrage)
{
	if (corewar && carrage)
	{
		return ;
	}
}
