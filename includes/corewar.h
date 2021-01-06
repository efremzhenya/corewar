/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:06:22 by lseema            #+#    #+#             */
/*   Updated: 2021/01/06 22:42:42 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "error.h"
# include "op.h"

typedef	struct			s_arg
{
	int					dump;
	int					n_pl;
}						t_arg;


typedef struct			s_player
{
	int					id;
	int					ind;
	char				*name;
	char				*comment;
	unsigned char		*code;
	size_t				size;
	struct s_player		*next;
}						t_player;

typedef struct			s_carrage
{
	size_t				id;
	int					carry;					//0 || 1
	unsigned int		op_code;				//код текущей операции
	size_t				cycle;
	unsigned int		pc;						//адрес следующей операции для выполнения
	int					registers[REG_NUMBER];
	struct s_carrage	*next;
}						t_carrage;

typedef struct			s_corewar
{
	unsigned char		*arena[MEM_SIZE];
	size_t				*block_owner[MEM_SIZE];
	size_t				cycles; 				//количество прошедших с начала игры циклов
	size_t				winner;					//игрок, о котором в последний раз сказали, что он жив
	size_t				curr_live;				//количество выполненных операций live за последний период, длинной в cycles_to_die
	size_t				cycles_to_die;			//длительность периода до проверки
	size_t				checks_imp;				//количество проведенных проверок
	struct s_player		*players;
	struct s_carrage	*carrages;
	struct s_op			*operations[17];
	t_arg				*cw_args;
}						t_corewar;

typedef struct			s_op
{
	char				*name;
	int					n_arg;
	int					args[3];
	int					number;
	int					cycles;
	char				*description;
	int					codage;
	int					carry;
}						t_op;

int						kill(char *msg);

/*
** Player
*/

t_player				*new_player(int *ac, char **av, t_corewar **corewar, int ind);
void					add_player(int *ac, char **av, t_corewar **corewar, int ind);
/*
** VM
*/

int						init_corewar(t_corewar **corewar);
void					exec_vm(t_corewar **corewar);

/*
** Parse
*/

int						parse_args(int argc, char **argv, t_corewar **corewar);

/*
** Free
*/

void					free_vm(t_corewar **corewar);

/*
** Carrage
*/
t_carrage				*new_carrage(size_t id);

#endif
