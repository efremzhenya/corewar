/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:04:29 by lseema            #+#    #+#             */
/*   Updated: 2021/01/23 17:38:56 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_sti(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[3];
	int i;

	offset = (carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type)) % MEM_SIZE;
	i = 0;
	while (i < 3)
	{
		if (carrage->op_args[i] == REG_CODE)
			arg[i] =
				carrage->registers[read_byte((*corewar)->arena, offset) - 1];
		else if (carrage->op_args[i] == IND_CODE)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = carrage->is_half_size_dir ?
				read_int16((*corewar)->arena, offset) :
				read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir, carrage->op_args[i++])
			% MEM_SIZE;
	}
	write_int32(corewar, carrage->pc + (arg[1] + arg[2]) % IDX_MOD, arg[0]);
}

void	op_fork(t_corewar **corewar, t_carrage *carrage)
{
	int			offset;
	int			pos;
	int			i;
	t_carrage	*cloned_carrage;

	offset = (carrage->pc + sizeof(t_op_type)) % MEM_SIZE;
	pos = (carrage->is_half_size_dir ? read_int16((*corewar)->arena, offset) :
		read_int32((*corewar)->arena, offset)) % IDX_MOD;
	cloned_carrage = new_carrage(pos, NULL);
	cloned_carrage->carry = carrage->carry;
	cloned_carrage->last_live_cycle = carrage->last_live_cycle;
	i = -1;
	while (++i < REG_NUMBER)
		cloned_carrage->registers[i] = carrage->registers[i];
	add_carrage(&(*corewar)->carrages, cloned_carrage);
}

void	op_lld(t_corewar **corewar, t_carrage *carrage)
{
	int reg;
	int offset;
	int value;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	reg = read_byte((*corewar)->arena, offset +
		get_arg_size(carrage->is_half_size_dir, carrage->op_args[0])) - 1;
	value = read_int32((*corewar)->arena, (carrage->op_args[0] == IND_CODE) ?
		carrage->pc + read_int16((*corewar)->arena, offset) : offset);
	carrage->registers[reg] = value;
	carrage->carry = !carrage->registers[reg];
}

void	op_lldi(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[3];
	int i;
	int reg;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	i = 0;
	while (i < 2)
	{
		if (carrage->op_args[i] == REG_CODE)
			arg[i] = read_byte((*corewar)->arena, offset) - 1;
		else if (carrage->op_args[i] == IND_CODE)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = carrage->is_half_size_dir ?
				read_int16((*corewar)->arena, offset) :
				read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset) - 1;
	carrage->registers[reg] =
		read_int32((*corewar)->arena, carrage->pc + (arg[0] + arg[1]));
	carrage->carry = !carrage->registers[reg];
}

void	op_lfork(t_corewar **corewar, t_carrage *carrage)
{
	int			offset;
	int			pos;
	int			i;
	t_carrage	*cloned_carrage;

	offset = (carrage->pc + sizeof(t_op_type)) % MEM_SIZE;
	pos = ((carrage->is_half_size_dir ? read_int16((*corewar)->arena, offset) :
		read_int32((*corewar)->arena, offset)) + carrage->pc) % MEM_SIZE;
	cloned_carrage = new_carrage(pos, NULL);
	cloned_carrage->carry = carrage->carry;
	cloned_carrage->last_live_cycle = carrage->last_live_cycle;
	i = -1;
	while (++i < REG_NUMBER)
		cloned_carrage->registers[i] = carrage->registers[i];
	add_carrage(&(*corewar)->carrages, cloned_carrage);
}
