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

int init_cor(t_asm *fc)
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
    return (1);
}

int asmparse(t_asm *fc)
{
    int err_count;
    
    err_count = 0;
    
    if (!init_cor(fc))
        terminate(ERR_3_READING_FAILED);
    
    return (err_count);
}
