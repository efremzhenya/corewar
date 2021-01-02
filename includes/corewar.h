/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:06:22 by lseema            #+#    #+#             */
/*   Updated: 2021/01/02 15:59:22 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

typedef struct			s_player
{
	size_t				id;
	char				*name;
	char				*comment;
	unsigned char		*code;
	size_t				size;
	struct s_player		*next;
}						t_player;

typedef struct			s_carrage
{
	size_t				id;
	unsigned int		carry;
	unsigned int		op_code;
	size_t				cycle;
	unsigned char		registers[REG_NUMBER];
	struct s_carrage	*next;
}						t_carrage;

typedef struct			s_corewar
{
	unsigned char		*arena[MEM_SIZE];
	size_t				cycles; 				//количество прошедших с начала игры циклов
	size_t				potential_winner;		//игрок, о котором в последний раз сказали, что он жив
	size_t				curr_live;				//количество выполненных операций live за последний период, длинной в cycles_to_die
	size_t				cycles_to_die;			//длительность периода до проверки
	size_t				checks_imp;				//количество проведенных проверок
	struct s_player		*players;
	struct s_carrage	*carrages;
}						t_corewar;

typedef struct			s_operation
{
	char				*name;
	int					n_arg;
	int					args[3];
	int					number;
	int					cicles;
	char				*description;
	int					codage;
	int					carry;
}						t_op;

int						kill(char *msg);

/*
** Player
*/

t_player				*new_player(size_t id, char *name, char *comment);
int						add_player(t_player **players, t_player *player);

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

#endif
