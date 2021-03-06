/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:40:04 by lseema            #+#    #+#             */
/*   Updated: 2021/01/21 21:47:30 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	parse_flags(int *ac, char **av, char flag, t_corewar **corewar)
{
	if (flag == 'd' && *ac == 1 && av[++(*ac)])
		(*corewar)->cw_args->dump = ft_atoi(av[(*ac)]);
	else if (flag == 'n' && (*corewar)->cw_args->n_pl == -1 && av[++(*ac)])
	{
		(*corewar)->cw_args->n_pl = ft_atoi(av[(*ac)]);
		if ((*corewar)->cw_args->n_pl > MAX_PLAYERS ||
			(*corewar)->cw_args->n_pl < 1)
			terminate(ERR_1_MAX_PLAYERS);
	}
	else
		terminate(COREWAR_USAGE);
	(*ac)++;
}

int		is_file(char *av, char *ext)
{
	char *s;

	s = av;
	while (*s)
		s++;
	s -= 4;
	return (ft_strcmp(s, ext));
}

int		parse_args(int argc, char **argv, t_corewar **corewar)
{
	int	i;
	int	ind;

	if (argc && *argv && corewar)
	{
		i = 1;
		ind = 0;
		while (i < argc)
		{
			if (!ft_strcmp(argv[i], "-dump"))
				parse_flags(&i, argv, 'd', corewar);
			else if (!ft_strcmp(argv[i], "-n"))
				parse_flags(&i, argv, 'n', corewar);
			else if (!is_file(argv[i], ".cor"))
			{
				add_player(&i, argv, corewar, ++ind);
				(*corewar)->players_count++;
			}
			else
				return (kill(COREWAR_USAGE));
		}
		fill_player_id(corewar);
		(*corewar)->players = sort_players((*corewar)->players);
	}
	return (*corewar)->players_count ? 1 : kill(COREWAR_USAGE);
}

void	fill_player_id(t_corewar **corewar)
{
	t_player	*tmp;
	t_player	*tmp2;
	int			j;

	tmp = (*corewar)->players;
	while (tmp)
	{
		if (tmp->id == 0)
		{
			j = tmp->ind;
			tmp2 = (*corewar)->players;
			while (tmp2 && j <= (*corewar)->players_count)
			{
				if (tmp2->id == j)
				{
					j++;
					tmp2 = (*corewar)->players;
				}
				else
					tmp2 = tmp2->next;
			}
			tmp->id = j;
		}
		tmp = tmp->next;
	}
}
