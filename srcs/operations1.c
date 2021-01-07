/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 22:51:17 by lseema            #+#    #+#             */
/*   Updated: 2021/01/08 00:10:23 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_corewar **corewar, t_carrage *carrage)
{
	t_player		*player;

	if (corewar && carrage)
	{
		carrage->last_live_cycle = (*corewar)->cycles;
		(*corewar)->lives++;
		if ((player = get_player_by_id(&(*corewar)->players,
			read_int32((*corewar)->arena,
			carrage->pc + sizeof(t_op_type)) * -1)))
		{
			(*corewar)->winner = player->id;
			alive_message(player);
		}
	}
}

void	op_ld(t_corewar **corewar, t_carrage *carrage)
{
	int reg;
	int offset;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	if (corewar && carrage)
	{
		reg = read_byte((*corewar)->arena,
			offset + get_arg_size(0, carrage->op_args[0]));
		if (carrage->op_args[0] == IND_CODE)
			offset = read_int16((*corewar)->arena, offset) % IDX_MOD;
		carrage->registers[reg] = read_int32((*corewar)->arena,
			carrage->pc + offset);
		carrage->carry = !carrage->registers[reg];
	}
}

void	op_st(t_corewar **corewar, t_carrage *carrage)
{
	int value;
	int pos;
	int offset;

	if (corewar && carrage)
	{
		offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
		if (carrage->op_args[1] == REG_CODE)
			value = carrage->registers[read_byte((*corewar)->arena,
				offset + get_arg_size(0, carrage->op_args[0]))];
		else
		{
			pos = carrage->pc + (read_int16((*corewar)->arena,
				offset + get_arg_size(0, carrage->op_args[0])) % IDX_MOD);
			value = read_int32((*corewar)->arena, pos);
		}
		carrage->registers[
			read_byte((*corewar)->arena, carrage->pc + offset)] = value;
	}
}

void	op_add(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int reg1_value;
	int reg2_value;
	int reg3_index;

	if (corewar && carrage)
	{
		offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
		reg1_value = carrage->registers[read_byte((*corewar)->arena, offset)];
		offset += get_arg_size(0, carrage->op_args[0]);
		reg2_value = carrage->registers[read_byte((*corewar)->arena, offset)];
		offset += get_arg_size(0, carrage->op_args[0]);
		reg3_index = read_byte((*corewar)->arena, offset);
		carrage->registers[reg3_index] = reg1_value + reg2_value;
		carrage->carry = !carrage->registers[reg3_index];
	}
}

void	op_sub(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int reg1_value;
	int reg2_value;
	int reg3_index;

	if (corewar && carrage)
	{
		offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
		reg1_value = carrage->registers[read_byte((*corewar)->arena, offset)];
		offset += get_arg_size(0, carrage->op_args[0]);
		reg2_value = carrage->registers[read_byte((*corewar)->arena, offset)];
		offset += get_arg_size(0, carrage->op_args[0]);
		reg3_index = read_byte((*corewar)->arena, offset);
		carrage->registers[reg3_index] = reg1_value - reg2_value;
		carrage->carry = !carrage->registers[reg3_index];
	}
}
