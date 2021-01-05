/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:06:22 by lseema            #+#    #+#             */
/*   Updated: 2021/01/05 21:08:22 by lseema           ###   ########.fr       */
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
	int					size;
	struct s_player		*next;
}						t_player;

typedef struct			s_carrage
{
	size_t				id;
	int					carry;					//0 || 1
	unsigned int		op_code;				//код текущей операции
	unsigned int		pc;						//адрес следующей операции для выполнения
	int					registers[REG_NUMBER];
	unsigned int		wait_cycles;			//кол-во циклов ожидания до выполнения
	size_t				last_live_cycle;		//цикл, в котором выполнялся последний live
	t_player			*player;
	struct s_carrage	*next;
}						t_carrage;

typedef struct			s_op
{
	char				*name;
	int					n_arg;
	int					args[3];
	int					number;
	unsigned int		cycles;
	char				*desc;
	int					is_arg_code;			//имеет код типов аргумента?
	int					is_half_size_dir;		//половинный размер t_dir(4 байта)?
}						t_op;

typedef struct			s_corewar
{
	unsigned char		arena[MEM_SIZE];
	size_t				block_owner[MEM_SIZE];
	size_t				cycles; 				//количество прошедших с начала игры циклов
	size_t				champion_id;			//игрок, о котором в последний раз сказали, что он жив
	size_t				lives;					//количество выполненных операций live за последний период, длинной в cycles_to_die
	size_t				cycles_to_die;			//длительность периода до проверки
	size_t				checks;					//количество проведенных проверок
	int					players_count;
	int					carrages_count;
	t_player			*players;
	t_carrage			*carrages;
	t_op				operations[17];
}						t_corewar;

int						kill(char *msg);

/*
** Player
*/

t_player				*new_player(size_t id, char *name, char *comment);
int						add_player(t_player **players, t_player *player);
void					free_players(t_player **players);

/*
** VM
*/

int						init_corewar(t_corewar **corewar);
void					start_vm(t_corewar **corewar);
void					intro_players(t_player **players);
void					do_cycle(t_corewar **corewar);
void					mock_generator(t_corewar **corewar);

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

t_carrage				*new_carrage(size_t id, unsigned int pc, t_player *player);
void					add_carrage(t_carrage **carrages, t_carrage *carrage);
void					init_carrages(t_corewar **corewar);
void					free_carrages(t_carrage **carrages);
void					die_carrages(t_corewar **corewar, t_carrage *current, t_carrage *del, t_carrage *temp);

/*
** Arena
*/

void					init_arena(t_corewar **corewar);

/*
** Operations
*/

void					set_operations(t_op	*op);

#endif
