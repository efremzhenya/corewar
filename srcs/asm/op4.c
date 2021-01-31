//
//  op4.c
//  corewar
//
//  Created by Christian Deadshot on 1/24/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

void					op_aff(t_asm **fc)
{
	t_op	op;
	op=(t_op){"aff", 0x10, 1, 1, {T_REG, 0, 0}, 4};
}
void					op_nop(t_asm **fc)
{
	
}

void					op_name(t_asm **fc)
{
	if((*fc)->code->valid_name == 0)
	{}
	else
	{
		(*fc)->s_err->str_num = (*fc)->s->str_num;
		(*fc)->s_err->str_str = (*fc)->s->str_str;
		(*fc)->s_err->str_err = "Champion's name is already known";
		(*fc)->warnings++;
		(*fc)->s_err->err_type = 'W';
		init_err_next((*fc));
	}

}

void					op_comment(t_asm **fc)
{
	if((*fc)->code->valid_comment == 0)
	{}
	else
	{
		(*fc)->s_err->str_num = (*fc)->s->str_num;
		(*fc)->s_err->str_str = (*fc)->s->str_str;
		(*fc)->s_err->str_err = "Champion's comment is already known";
		(*fc)->warnings++;
		(*fc)->s_err->err_type = 'W';
		init_err_next((*fc));
	}
}

void					op_label(t_asm **fc)
{
	
}
