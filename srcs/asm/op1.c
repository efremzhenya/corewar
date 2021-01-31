//
//  op1.c
//  corewar
//
//  Created by Christian Deadshot on 1/24/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

void					op_live(t_asm **fc)
{
	t_op	op;
	op=(t_op){"live", 0x01, 1, 0, {T_DIR}, 4};
}
void					op_ld(t_asm **fc)
{
	t_op	op;
	op=(t_op){"ld", 0x02, 2, 1, {T_DIR | T_IND, T_REG, 0}, 4};
}

void					op_st(t_asm **fc)
{
	t_op	op;
	op=(t_op){"st", 0x03, 2, 1, {T_REG, T_REG | T_IND, 0}, 4};
}
void					op_add(t_asm **fc)
{
	t_op	op;
	op=(t_op){"add", 0x04, 3, 1, {T_REG, T_REG, T_REG}, 4};
}
void					op_sub(t_asm **fc)
{
	t_op	op;
	op=(t_op){"sub", 0x05, 3, 1, {T_REG, T_REG, T_REG}, 4};
}
