/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corwar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:05:57 by lseema            #+#    #+#             */
/*   Updated: 2020/12/30 22:16:16 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct		s_player
{
	size_t			id;
	char			*name;
	char			*comment;
	unsigned char	*code;
	size_t			size;
}					t_player;

typedef struct		s_carrage
{
	size_t			id;
	unsigned int	carry;
	unsigned int	op_code;
	size_t			cycle;
	...
}					t_carrage;

typedef struct		s_corewar
{
	unsigned char	*arena[];
	size_t			cycles; 				//количество прошедших с начала игры циклов
	size_t			potential_winner;		//игрок, о котором в последний раз сказали, что он жив
	size_t			curr_live;				//количество выполненных операций live за последний период, длинной в cycles_to_die
	size_t			cycles_to_die;			//длительность периода до проверки
	size_t			checks_imp;				//количество проведенных проверок
	...
}					t_corewar;

typedef struct		s_op
{
	char			*name;
	int				n_arg;
	int				args[3];
	int				number;
	int				cicles;
	char			*description;
	int				codage;
	int				carry;
}					t_op;
