//
//  err.c
//  corewar_asm
//
//  Created by Christian Deadshot on 2/6/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

void	write_err(t_asm *fc, char *err_msg, char err_type)
{
	init_err(fc);
	
	if (err_type == 'C')
		fc->critical++;
	if (err_type == 'W')
		fc->warnings++;
	if (err_type == 'I')
		fc->ignored++;
	fc->s_err->err_type = err_type;
	fc->s_err->str_err = err_msg;
	fc->s_err->str_num = fc->s->str_num;
	fc->s_err->str_str = fc->s->str_str;
}

void	write_cerr(t_asm *fc, char *err_msg)
{
	init_err(fc);
	fc->s_err->str_err = err_msg;
	fc->critical++;
	fc->s_err->err_type = 'C';
	fc->s_err->str_num = fc->s->str_num;
	fc->s_err->str_str = fc->s->str_str;
}

void	write_werr(t_asm *fc, char *err_msg)
{
	init_err(fc);
	fc->s_err->str_err = err_msg;
	fc->warnings++;
	fc->s_err->err_type = 'W';
	fc->s_err->str_num = fc->s->str_num;
	fc->s_err->str_str = fc->s->str_str;
}

void	write_ierr(t_asm *fc, char *err_msg)
{
	init_err(fc);
	fc->s_err->str_err = err_msg;
	fc->ignored++;
	fc->s_err->err_type = 'I';
	fc->s_err->str_num = fc->s->str_num;
	fc->s_err->str_str = fc->s->str_str;
}
