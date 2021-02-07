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

int			is_label_valid(char *label)
{
	int 	i;
	
	i = 0;
	while (label[i] != '\0')
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
			return(0);
		i++;
	}
	return(1);
}

t_asms		*op_label(t_asm **fc)
{
	t_asms	*current_str;
	char	**label_ar;
	
	current_str = (*fc)->s;
	label_ar = ft_strsplit((*fc)->s->str_str, LABEL_CHAR);
	if(!is_label_valid(label_ar[0]))
	{
		write_err((*fc), "SYNTAX ERROR: Bad label", 'C');
		return (current_str);
	}
	if (ft_strtrim(label_ar[1]) == NULL)
	{
		init_label((*fc));
		(*fc)->label->label = label_ar[0];
	}
	else
		write_err((*fc), "SYNTAX ERROR", 'C');
	current_str = (*fc)->s->next;
	return (current_str);
}
