/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_asm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:05:14 by lseema            #+#    #+#             */
/*   Updated: 2021/01/21 21:32:23 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		set_operations(t_op_o *op)
{
	
	op[0] = (t_op_o){"nop", 0, {0}, 0, 0, 0, 0, 0, op_nop};
	op[1] = (t_op_o){"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, op_live};
	op[2] = (t_op_o){"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, op_ld};
	op[3] = (t_op_o){"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, op_st};
	op[4] = (t_op_o){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "add", 1, 0, op_add};
	op[5] = (t_op_o){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0,
		op_sub};
	op[6] = (t_op_o){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR,
		T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, op_and};
	op[7] = (t_op_o){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR,
		T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, op_or};
	op[8] = (t_op_o){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR,
		T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, op_xor};
	op[9] = (t_op_o){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, op_zjmp};
	op[10] = (t_op_o){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10,
		25, "load index", 1, 1, op_ldi};
	op[11] = (t_op_o){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11,
		25, "store index", 1, 1, op_sti};
	op[12] = (t_op_o){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, op_fork};
	op[13] = (t_op_o){"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0,
		op_lld};
	op[14] = (t_op_o){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, "long load index", 1, 1, op_lldi};
	op[15] = (t_op_o){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, op_lfork};
	op[16] = (t_op_o){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, op_aff};
	
//	static t_op		g_op[16] = {
//		{
//			.name = "live",
//			.code = 0x01,
//			.args_num = 1,
//			.args_types_code = false,
//			.args_types = {T_DIR, 0, 0},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "ld",
//			.code = 0x02,
//			.args_num = 2,
//			.args_types_code = true,
//			.args_types = {T_DIR | T_IND, T_REG, 0},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "st",
//			.code = 0x03,
//			.args_num = 2,
//			.args_types_code = true,
//			.args_types = {T_REG, T_REG | T_IND, 0},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "add",
//			.code = 0x04,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG, T_REG, T_REG},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "sub",
//			.code = 0x05,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG, T_REG, T_REG},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "and",
//			.code = 0x06,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "or",
//			.code = 0x07,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "xor",
//			.code = 0x08,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "zjmp",
//			.code = 0x09,
//			.args_num = 1,
//			.args_types_code = false,
//			.args_types = {T_DIR, 0, 0},
//			.t_dir_size = 2,
//		},
//		{
//			.name = "ldi",
//			.code = 0x0A,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
//			.t_dir_size = 2,
//		},
//		{
//			.name = "sti",
//			.code = 0x0B,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
//			.t_dir_size = 2,
//		},
//		{
//			.name = "fork",
//			.code = 0x0C,
//			.args_num = 1,
//			.args_types_code = false,
//			.args_types = {T_DIR, 0, 0},
//			.t_dir_size = 2,
//		},
//		{
//			.name = "lld",
//			.code = 0x0D,
//			.args_num = 2,
//			.args_types_code = true,
//			.args_types = {T_DIR | T_IND, T_REG, 0},
//			.t_dir_size = 4,
//		},
//		{
//			.name = "lldi",
//			.code = 0x0E,
//			.args_num = 3,
//			.args_types_code = true,
//			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
//			.t_dir_size = 2,
//		},
//		{
//			.name = "lfork",
//			.code = 0x0F,
//			.args_num = 1,
//			.args_types_code = false,
//			.args_types = {T_DIR, 0, 0},
//			.t_dir_size = 2,
//		},
//		{
//			.name = "aff",
//			.code = 0x10,
//			.args_num = 1,
//			.args_types_code = true,
//			.args_types = {T_REG, 0, 0}, --- ?????????
//			.t_dir_size = 4,
//		}
//	};
// + сделать массив op[0] = {"кодовое слово", имяфункции};
}
