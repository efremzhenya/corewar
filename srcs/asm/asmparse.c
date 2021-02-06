/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asmparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:51:06 by mellie            #+#    #+#             */
/*   Updated: 2021/01/22 21:37:15 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ignored_line(t_asm *fc)
{
	int	i;
	i = 0;

	while ((fc->s->str_str[i] == ' ') ||
		(fc->s->str_str[i] == '\t'))
		i++;
	if (i == ft_strlen(fc->s->str_str) ||
	(fc->s->str_str[i] == COMMENT_CHAR))
		write_err(fc, "Ignored line", 'I');
	else
		write_err(fc, "Syntax error", 'C');
}

int	find_op(char *str)
{
	t_op_list	ol[20];
	int			i;
	
	i = 0;
	set_op_list(ol);
	while (i < 20)
	{
		if (ft_strstr(str, ol[i].name) != NULL)
		{
			return (i);
		}
		i++;
	}
	return(i);
}

int	parse(t_asm *fc)
{
	t_op_list	ol[20];
	int			i;
	
	set_op_list(ol);
	
	fc->s = fc->first_s;
	while (fc->s->next)
	{
		i = find_op(fc->s->str_str);
		if ( i < 20)
			ol[i].f(&fc);
		else
			ignored_line(fc);
		fc->s = fc->s->next;
	}
	return (1);
}

int init_header(t_asm *fc)
{
    int i;
    
    i = 0;
    fc->code = (t_bytecode *)malloc(sizeof(t_bytecode));
    err_allocate(fc->code);
    fc->code->header.magic = COREWAR_EXEC_MAGIC;
    fc->code->header.prog_size = 0;
    while (i <= PROG_NAME_LENGTH)
        fc->code->header.prog_name[i++] = 0;
    i = 0;
    while (i <= COMMENT_LENGTH)
        fc->code->header.comment[i++] = 0;
	fc->code->valid_name = 0;
	fc->code->valid_comment = 0;
	fc->code->cpos = 0;
	fc->code->exec_size = 0;
	fc->code->code = (char *)malloc(sizeof(char) * 4);
	int_to_bytecode(fc, COREWAR_EXEC_MAGIC, 4);
	
    return (1);
}

int asmparse(t_asm *fc)
{
    int err_count;
    
    err_count = 0;
    
    if (!init_header(fc))
        terminate(ERR_3_READING_FAILED);
//    if (!init_ce(fc))
//        terminate(ERR_3_READING_FAILED);
    if (!parse(fc))
        terminate(SYNTAX_ERROR);
    
    return (err_count);
}
