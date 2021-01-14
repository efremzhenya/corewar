/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:04:29 by lseema            #+#    #+#             */
/*   Updated: 2021/01/14 22:12:12 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
		if (carrage->op_args[i] == REG_CODE)
			arg[i] = read_byte((*corewar)->arena, offset);
		else if (carrage->op_args[i] == IND_CODE)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset);
	carrage->carry = !(carrage->registers[reg] = arg[0] & arg[1]);
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
		if (carrage->op_args[i] == REG_CODE)
			arg[i] = read_byte((*corewar)->arena, offset);
		else if (carrage->op_args[i] == IND_CODE)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset);
	carrage->carry = !(carrage->registers[reg] = arg[0] | arg[1]);
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
		if (carrage->op_args[i] == REG_CODE)
			arg[i] = read_byte((*corewar)->arena, offset);
		else if (carrage->op_args[i] == IND_CODE)
			arg[i] = read_int32((*corewar)->arena, carrage->pc
				+ (read_int16((*corewar)->arena, offset) % IDX_MOD));
		else
			arg[i] = read_int32((*corewar)->arena, offset);
		offset += get_arg_size(carrage->is_half_size_dir,
			carrage->op_args[i++]);
	}
	reg = read_byte((*corewar)->arena, offset);
	carrage->carry = !(carrage->registers[reg] = arg[0] ^ arg[1]);
}

void	op_zjmp(t_corewar **corewar, t_carrage *carrage)
{
	int offset;

	offset = carrage->pc + sizeof(t_op_type);
	if (carrage->carry)
		carrage->pc = ((read_int16((*corewar)->arena, offset) % IDX_MOD)
			+ carrage->pc) % MEM_SIZE;
}

void	op_ldi(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int arg[3];
	int i;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	i = 0;
	while (i < 3)
	{
		if (carrage->op_args[i] == REG_CODE)
			arg[i] = read_byte((*corewar)->arena, offset);
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
	carrage->registers[arg[2]] = carrage->pc + (arg[0] + arg[1]) % IDX_MOD;
}
