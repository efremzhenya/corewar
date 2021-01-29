//
//  op2.c
//  corewar
//
//  Created by Christian Deadshot on 1/24/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

void					op_and(t_asm **fc)
{
	t_op        op=(t_op){"and", 0x06, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4};
}
void					op_or(t_asm **fc)
{
	t_op        op=(t_op){"or", 0x07, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4};
}

void					op_xor(t_asm **fc)
{
	t_op        op=(t_op){"xor", 0x08, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4};
}
void					op_zjmp(t_asm **fc)
{
	t_op        op=(t_op){"zjmp", 0x09, 1, 0, {T_DIR, 0, 0}, 2};
}
void					op_ldi(t_asm **fc)
{
	t_op        op=(t_op){"ldi", 0x0A, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 2};
}
