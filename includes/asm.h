/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:50:42 by mellie            #+#    #+#             */
/*   Updated: 2021/01/22 21:37:22 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef asm_h
# define asm_h

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
//# include "corewar.h"
# include "op.h"
# include "error.h"

typedef struct		s_asms
{
	int				str_num;
	char			*str_str;
	struct s_asms	*next;
}					t_asms;

typedef struct		s_asmerr
{
	int				str_num;
	char			*str_str;
	char			*str_err;
	struct s_asmerr	*next;
}					t_asmerr;

typedef struct			s_asmcor
{
	t_asms				*str_s;
	char				*label;
	int					start_byte;
	int					len;
	int					corstr_num;
	char				*corstr_str;
	struct s_asmcor		*next;
}						t_asmcor;

typedef struct		s_bytecode
{
	t_header		header;
	char			*code;
}					t_bytecode;

typedef struct	s_asm
{
    int			fd;
    int			fw;
    char		*str;
	char		*ex_file;
	t_asms		*s;
	t_asms		*first_s;
	t_asmerr	*s_err;
	t_asmerr	*first_err;
	t_asmcor	*cor;
	t_asmcor	*first_cor;
	t_bytecode	*code;
}				t_asm;

typedef struct			s_op
{
	char				*name;
	int					n_arg;
	int					args[3];
	int					op_type;
	unsigned int		cycles;
	char				*desc;
	int					is_arg_code;
	int					is_half_size_dir;
	void				(*f)(t_asm **);
}						t_op;

int 	init_header(t_asm *fc);
int		ft_read_sfile(t_asm *fc);
int		ft_write_corfile(t_asm *fc);
int		init_fc(t_asm *fc, const char *av);
int		asmparse(t_asm *fc);

char	*ft_itoa_base(int value, int base);
int		ft_hex_to_dec(char *s);
char	*ft_dec_to_hex(int dec);

void					set_operations(t_op	*op);
void					op_live(t_asm **fc);
void					op_ld(t_asm **fc);
void					op_st(t_asm **fc);
void					op_add(t_asm **fc);
void					op_sub(t_asm **fc);
void					op_and(t_asm **fc);
void					op_or(t_asm **fc);
void					op_xor(t_asm **fc);
void					op_zjmp(t_asm **fc);
void					op_ldi(t_asm **fc);
void					op_sti(t_asm **fc);
void					op_fork(t_asm **fc);
void					op_lld(t_asm **fc);
void					op_lldi(t_asm **fc);
void					op_lfork(t_asm **fc);
void					op_aff(t_asm **fc);
void					op_nop(t_asm **fc);

#endif /* asm_h */
