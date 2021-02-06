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
	t_asms	*current_str;
	if((*fc)->code->valid_name == 0)
	{
		if ((current_str = read_str((*fc)->code->header.prog_name,
									PROG_NAME_LENGTH, (*fc)->s)))
		{
			(*fc)->code->valid_name++;
			(*fc)->s = current_str;
		}
		else
			write_err((*fc), "Syntax error", 'C');
	}
	else
		write_err((*fc), "Champion's name is already known", 'W');
}

void					op_comment(t_asm **fc)
{
	t_asms	*current_str;
	if((*fc)->code->valid_comment == 0)
	{
		if ((current_str =read_str((*fc)->code->header.comment,
								   COMMENT_LENGTH, (*fc)->s)))
		{
			(*fc)->code->valid_comment++;
			(*fc)->s = current_str;
		}
		else
			write_err((*fc), "Syntax error", 'C');
	}
	else
		write_err((*fc), "Champion's comment is already known", 'W');
}

void					op_label(t_asm **fc)
{
	
}
