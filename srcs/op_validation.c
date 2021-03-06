/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:14:20 by lseema            #+#    #+#             */
/*   Updated: 2021/01/24 01:08:53 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		chk_arg_type(t_op op, t_carrage *carrage, unsigned char *arena)
{
	int	i;
	int	type;

	i = -1;
	if (op.is_arg_code)
	{
		type = read_byte(arena, carrage->pc + sizeof(t_op_type));
		carrage->op_args[0] =
			((type & 0b11000000) >> 6 << 2) / 3 * (op.n_arg >= 1);
		carrage->op_args[1] =
			((type & 0b00110000) >> 4 << 2) / 3 * (op.n_arg >= 2);
		carrage->op_args[2] =
			((type & 0b00001100) >> 2 << 2) / 3 * (op.n_arg >= 3);
		while (++i < op.n_arg)
			if (!(op.args[i] & carrage->op_args[i]))
				return (0);
	}
	else
		while (++i < op.n_arg)
			carrage->op_args[i] = op.args[i];
	return (chk_regs(op, carrage, arena));
}

int		chk_regs(t_op op, t_carrage *carrage, unsigned char *arena)
{
	int				offset;
	unsigned char	reg;
	int				i;

	offset = sizeof(t_op_type) + (op.is_arg_code ? sizeof(t_arg_type) : 0);
	i = 0;
	while (i < op.n_arg)
	{
		if (carrage->op_args[i] == T_REG)
		{
			reg = read_byte(arena, carrage->pc + offset);
			if (reg < 1 || reg > REG_NUMBER)
				return (0);
		}
		offset += get_arg_size(op.is_half_size_dir, carrage->op_args[i++]);
	}
	return (offset);
}
