//
//  op3.c
//  corewar
//
//  Created by Christian Deadshot on 1/24/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

void					op_sti(t_asm **fc)
{
	t_op        op=(t_op){"sti", 0x0B, 3, 1, {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}, 2};
}
void					op_fork(t_asm **fc)
{
	t_op        op=(t_op){"fork", 0x0C, 1, 0, {T_DIR, 0, 0}, 2};
}

void					op_lld(t_asm **fc)
{
	t_op        op=(t_op){"lld", 0x0D, 2, 1, {T_DIR | T_IND, T_REG, 0}, 4};
}
void					op_lldi(t_asm **fc)
{
	t_op        op=(t_op){"lldi", 0x0E, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 2};
}
void					op_lfork(t_asm **fc)
{
	t_op        op=(t_op){"lfork", 0x0F, 1, 0, {T_DIR, 0, 0}, 2};
}
