/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:14:20 by lseema            #+#    #+#             */
/*   Updated: 2021/01/09 11:17:55 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		chk_arg_type(t_op op, t_carrage *carrage, unsigned char *arena)
{
	int		i;
	int		arg_type;

	i = -1;
	if (op.is_arg_code)
	{
		arg_type = read_byte(arena, carrage->pc + sizeof(t_op_type));
		carrage->op_args[0] = op.n_arg >= 1 ? (arg_type & 0b11000000) >> 6 : 0;
		carrage->op_args[1] = op.n_arg >= 2 ? (arg_type & 0b00110000) >> 4 : 0;
		carrage->op_args[2] = op.n_arg >= 3 ? (arg_type & 0b00001100) >> 2 : 0;
		while (++i < op.n_arg)
			if (!(op.args[i] & carrage->op_args[i]))
				return (0);
	}
	else
		while (++i < op.n_arg)
		{
			if (op.args[i] == T_REG)
				carrage->op_args[i] = REG_CODE;
			else if (op.args[i] == T_DIR)
				carrage->op_args[i] = DIR_CODE;
			else
				carrage->op_args[i] = IND_CODE;
		}
	return chk_regs(op, carrage, arena);
}

int		chk_regs(t_op op, t_carrage *carrage, unsigned char *arena)
{
	int				offset;
	unsigned char	reg;
	int				i;

	offset = sizeof(t_op_type) + op.is_arg_code ? sizeof(t_arg_type) : 0;
	i = 0;
	while (i < op.n_arg)
	{
		if (carrage->op_args[i] == REG_CODE &&
			((reg = read_byte(arena, carrage->pc + ++offset)) < 1 || reg > REG_NUMBER))
				return (0);
		offset += get_arg_size(op.is_half_size_dir, carrage->op_args[i++]);
	}
	return (offset);
}

int		instruction_size(t_carrage *carrage, t_op op)
{
	int offset;
	int i;

	i = 0;
	offset = sizeof(t_op_type) + op.is_arg_code ? sizeof(t_arg_type) : 0;
	while (i < op.n_arg)
		offset += get_arg_size(op.is_half_size_dir, carrage->op_args[i++]);
	return offset;
}
