/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 22:51:17 by lseema            #+#    #+#             */
/*   Updated: 2021/01/31 01:29:36 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_corewar **corewar, t_carrage *carrage)
{
	t_player		*player;

	carrage->last_live_cycle = (*corewar)->cycles;
	(*corewar)->lives++;
	if ((player = get_player_by_id(&(*corewar)->players,
		read_int32((*corewar)->arena, carrage->pc + sizeof(t_op_type)) * -1)))
	{
		(*corewar)->winner = player->id;
		if ((*corewar)->cw_args->dump == -1 && !(*corewar)->cw_args->visual)
			alive_message(player);
	}
}

void	op_ld(t_corewar **corewar, t_carrage *carrage)
{
	int reg;
	int offset;
	int value;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	reg = read_byte((*corewar)->arena, offset +
		get_arg_size(carrage->is_half_size_dir, carrage->op_args[0])) - 1;
	value = read_int32((*corewar)->arena, (carrage->op_args[0] == T_IND) ?
		carrage->pc + read_int16((*corewar)->arena, offset) % IDX_MOD : offset);
	carrage->registers[reg] = value;
	carrage->carry = !carrage->registers[reg];
}

void	op_st(t_corewar **corewar, t_carrage *carrage)
{
	int pos;
	int offset;
	int reg;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	reg = read_byte((*corewar)->arena, offset) - 1;
	offset += get_arg_size(carrage->is_half_size_dir, carrage->op_args[0]);
	if (carrage->op_args[1] == T_REG)
		carrage->registers[read_byte((*corewar)->arena, offset) - 1] =
			carrage->registers[reg];
	else
	{
		pos = carrage->pc + read_int16((*corewar)->arena, offset) % IDX_MOD;
		write_int32(corewar, pos, carrage->registers[reg], carrage->player->id);
	}
}

void	op_add(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int reg1_value;
	int reg2_value;
	int reg3_index;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	reg1_value = carrage->registers[read_byte((*corewar)->arena, offset) - 1];
	offset += get_arg_size(carrage->is_half_size_dir, carrage->op_args[0]);
	reg2_value = carrage->registers[read_byte((*corewar)->arena, offset) - 1];
	offset += get_arg_size(carrage->is_half_size_dir, carrage->op_args[0]);
	reg3_index = read_byte((*corewar)->arena, offset);
	carrage->registers[reg3_index - 1] = reg1_value + reg2_value;
	carrage->carry = !carrage->registers[reg3_index - 1];
}

void	op_sub(t_corewar **corewar, t_carrage *carrage)
{
	int offset;
	int reg1_value;
	int reg2_value;
	int reg3_index;

	offset = carrage->pc + sizeof(t_op_type) + sizeof(t_arg_type);
	reg1_value = carrage->registers[read_byte((*corewar)->arena, offset) - 1];
	offset += get_arg_size(carrage->is_half_size_dir, carrage->op_args[0]);
	reg2_value = carrage->registers[read_byte((*corewar)->arena, offset) - 1];
	offset += get_arg_size(carrage->is_half_size_dir, carrage->op_args[0]);
	reg3_index = read_byte((*corewar)->arena, offset);
	carrage->registers[reg3_index - 1] = reg1_value - reg2_value;
	carrage->carry = !carrage->registers[reg3_index - 1];
}
