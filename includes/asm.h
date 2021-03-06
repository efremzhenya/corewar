/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:50:42 by mellie            #+#    #+#             */
/*   Updated: 2021/01/28 23:30:15 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef asm_h
# define asm_h
# define NBR_OP		20

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "op.h"
# include "error.h"

typedef struct		s_asms
{
	int				str_num;
	char			*str_str;
	struct s_asms	*next;
}					t_asms;

typedef struct		s_label
{
	char			*label;
	int				start_byte;
	struct s_label	*prev;
	struct s_label	*next;
}					t_label;

typedef struct		s_asmerr
{
	int				str_num;
	char			*str_str;
	char			*str_err;
	char			err_type; //Warning|Critical|Ignored
	struct s_asmerr	*next;
}					t_asmerr;

typedef struct			s_asmcor
{
	t_asms				*str_s;
	char				*label;
	int					start_byte;
	int					len;
	uint8_t				op_code;
	char				*args_str;
	int					corstr_num;
	char				*corstr_str;
	struct s_asmcor		*next;
}						t_asmcor;

typedef struct		s_bytecode
{
	t_header		header;
	int				valid_name;
	int				valid_comment;
	char			*code;
	int				exec_size;
	int				cpos;
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
	int			warnings;
	int			critical;
	int			ignored;
	t_asmcor	*cor;
	t_asmcor	*first_cor;
	t_label		*label;
	t_bytecode	*code;
}				t_asm;

typedef struct			s_op_o
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
}						t_op_o;

typedef struct			s_op_list
{
	char				*name;
	void				(*f)(t_asm **);
}						t_op_list;

typedef struct	s_op
{
    char		*name;
    uint8_t		code;
    uint8_t		args_num;
    int			args_types_code;
    uint8_t		args_types[3];
    uint8_t		t_dir_size;
}				t_op;

int 	init_header(t_asm *fc);
int		ft_read_sfile(t_asm *fc);
int		ft_write_corfile(t_asm *fc);
int		init_fc(t_asm *fc, const char *av);
int		asmparse(t_asm *fc);
int		parse(t_asm *fc);
int		init_cor(t_asm *fc);
int		init_err(t_asm *fc);
int		init_label(t_asm *fc);
void	del_prev_labels(t_asm *fc);

t_asms		*new_s(void);
t_asmcor	*new_cor(void);
t_asmerr	*new_err(void);
t_label		*new_label(void);

void		write_err(t_asm *fc, char *err_msg, char err_type);

void		ignored_line(t_asm *fc);
int			parse_name(t_asm **fc);
int			find_op(char *str);
t_asms		*read_str(char *dest, int len, t_asms *s);

char	*ft_itoa_base(int value, int base);
int		ft_hex_to_dec(char *s);
char	*ft_dec_to_hex(int dec);
void	int_to_bytecode(t_asm *fc, int value, int len);
char	*int_to_bytecode_ch(int value, int len);

void					set_operations(t_op_o	*op);
void					set_op_list(t_op_list *ol);
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
void					op_name(t_asm **fc);
void					op_comment(t_asm **fc);
//void					op_label(t_asm **fc);
t_asms					*op_label(t_asm **fc);

#endif /* asm_h */
