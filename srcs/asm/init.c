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

t_asmerr	*new_err(void)
{
	t_asmerr	*s;
	s = (t_asmerr *)malloc(sizeof(t_asmerr));
	err_allocate(s);
	s->next = NULL;
	return (s);
}

int	init_cor_next(t_asm *fc)
{
	fc->cor->next = (t_asmcor *)malloc(sizeof(t_asmcor));
	err_allocate(fc->cor->next);
	fc->cor = fc->cor->next;
	fc->cor->next = NULL;

	return (1);
}

int	init_err_next(t_asm *fc)
{
	fc->s_err->next = (t_asmerr *)malloc(sizeof(t_asmerr));
	err_allocate(fc->s_err->next);
	fc->s_err = fc->s_err->next;
	fc->s_err->str_err = "\0";
	fc->s_err->str_str = "\0";
	fc->s_err->next = NULL;

	return (1);
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

int	init_ce(t_asm *fc)
{
	fc->cor = (t_asmcor *)malloc(sizeof(t_asmcor));
	err_allocate(fc->cor);
	fc->cor->next = NULL;
	fc->first_cor = fc->cor;
	
	fc->s_err = (t_asmerr *)malloc(sizeof(t_asmerr));
	err_allocate(fc->s_err);
	fc->s_err->str_err = "\0";
	fc->s_err->str_str = "\0";
	fc->s_err->next = NULL;
	fc->first_err = fc->s_err;
	
	return (1);
}
