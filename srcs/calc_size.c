/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:55:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/09 11:57:34 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_arg_size(int is_half_sized_dir, int type)
{
	if (type == REG_CODE)
		return (get_reg_index_size());
	else if (type == IND_CODE)
		return (IND_SIZE);
	else if (type == DIR_CODE)
		return (is_half_sized_dir) ? DIR_SIZE / 2 : DIR_SIZE;
	else
		return (0);
}

int			get_reg_index_size()
{
	size_t	reg_num;
	int		bytes;

	reg_num = REG_NUMBER;
	bytes = 0;
	while (reg_num != 0)
	{
		reg_num /= (1u << 8);
		bytes++;
	}
	return (bytes);
}

int			instruction_size(t_carrage *carrage, t_op op)
{
	int offset;
	int i;

	i = 0;
	offset = sizeof(t_op_type) + op.is_arg_code ? sizeof(t_arg_type) : 0;
	while (i < op.n_arg)
		offset += get_arg_size(op.is_half_size_dir, carrage->op_args[i++]);
	return offset;
}
