/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:04:29 by lseema            #+#    #+#             */
/*   Updated: 2021/02/03 23:10:05 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	op_and(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[2];
	int i;
	int reg;

	i = 0;
	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	while (i < 2)
	{
		if (carrage->op_args[i] == T_REG)
			arg[i] =
				carrage->registers[read_byte((*corewar)->arena, offset) - 1];
		else if (carrage->op_args[i] == T_IND)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset) - 1;
	carrage->registers[reg] = arg[0] & arg[1];
	carrage->carry = !(carrage->registers[reg]);
}

void	op_or(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[2];
	int i;
	int reg;

	i = 0;
	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	while (i < 2)
	{
		if (carrage->op_args[i] == T_REG)
			arg[i] =
				carrage->registers[read_byte((*corewar)->arena, offset) - 1];
		else if (carrage->op_args[i] == T_IND)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset) - 1;
	carrage->registers[reg] = arg[0] | arg[1];
	carrage->carry = !(carrage->registers[reg]);
}

void	op_xor(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[2];
	int i;
	int reg;

	i = 0;
	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	while (i < 2)
	{
		if (carrage->op_args[i] == T_REG)
			arg[i] =
				carrage->registers[read_byte((*corewar)->arena, offset) - 1];
		else if (carrage->op_args[i] == T_IND)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset) - 1;
	carrage->registers[reg] = arg[0] ^ arg[1];
	carrage->carry = !(carrage->registers[reg]);
}

void	op_zjmp(t_corewar **corewar, t_carrage *carrage)
{
	int offset;

	offset = carrage->pc + sizeof(t_op_type);
	if (carrage->carry)
	{
		carrage->pc = (carrage->pc + read_int16((*corewar)->arena, offset)
			% IDX_MOD) % MEM_SIZE;
		if ((*corewar)->cw_args->visual)
			(*corewar)->visual->sound.jump = 1;
	}
}

void	op_ldi(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[3];
	int i;
	int reg;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	i = 0;
	while (i < 2)
	{
		if (carrage->op_args[i] == T_REG)
			arg[i] =
				carrage->registers[read_byte((*corewar)->arena, offset) - 1];
		else if (carrage->op_args[i] == T_IND)
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
	carrage->registers[reg] = read_int32((*corewar)->arena,
		carrage->pc + (arg[0] + arg[1]) % IDX_MOD);
}
