//
//  init.c
//  corewar_asm
//
//  Created by Christian Deadshot on 1/30/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

t_asmcor	*new_cor(void)
{
	t_asmcor	*s;
	s = (t_asmcor *)malloc(sizeof(t_asmcor));
	err_allocate(s);
	s->next = NULL;
	return (s);
}

int	init_cor(t_asm *fc)
{
	if (fc->first_cor == NULL)
	{
		fc->cor = new_cor();
		fc->first_cor = fc->cor;
	}
	else
	{
		fc->cor->next = new_cor();
		fc->cor = fc->cor->next;
	}
	return (1);
}

t_asmerr	*new_err(void)
{
	t_asmerr	*s;
	s = (t_asmerr *)malloc(sizeof(t_asmerr));
	err_allocate(s);
	s->next = NULL;
	return (s);
}

int	init_err(t_asm *fc)
{
	if (fc->first_err == NULL)
	{
		fc->s_err = new_err();
		fc->first_err = fc->s_err;
	}
	else
	{
		fc->s_err->next = new_err();
		fc->s_err = fc->s_err->next;
	}
	return (1);
}

t_label	*new_label(void)
{
	t_label	*s;
	s = (t_label *)malloc(sizeof(t_label));
	err_allocate(s);
	s->next = NULL;
	s->start_byte = -1;
	return (s);
}

int	init_label(t_asm *fc)
{
	if (fc->label == NULL)
	{
		fc->label = new_label();
		fc->label->prev = NULL;
	}
	else
	{
		fc->label->next = new_label();
		fc->label->next->prev = fc->label;
		fc->label = fc->label->next;
	}
	return (1);
}

