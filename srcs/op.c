/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:05:14 by lseema            #+#    #+#             */
/*   Updated: 2021/01/15 01:05:42 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		set_operations(t_op	*op)
{
	op[0] = (t_op){"nop", 0, {0}, 0, 0, 0, 0, 0, op_nop};
	op[1] = (t_op){"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, op_live};
	op[2] = (t_op){"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, op_ld};
	op[3] = (t_op){"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, op_st};
	op[4] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "add", 1, 0, op_add};
	op[5] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0,
		op_sub};
	op[6] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR,
		T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, op_and};
	op[7] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR,
		T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, op_or};
	op[8] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR,
		T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, op_xor};
	op[9] = (t_op){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, op_zjmp};
	op[10] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10,
		25, "load index", 1, 1, op_ldi};
	op[11] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11,
		25, "store index", 1, 1, op_sti};
	op[12] = (t_op){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, op_fork};
	op[13] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0,
		op_lld};
	op[14] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, "long load index", 1, 1, op_lldi};
	op[15] = (t_op){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, op_lfork};
	op[16] = (t_op){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, op_aff};
}
