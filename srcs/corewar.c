/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:05:57 by lseema            #+#    #+#             */
/*   Updated: 2021/01/16 23:37:43 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		kill(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (0);
}

int		main(int argc, char **argv)
{
	t_corewar	*corewar;

	corewar = NULL;
	if (argc > 1)
	{
		if (init_corewar(&corewar) && parse_args(argc, argv, &corewar))
		{
			start_vm(&corewar);
		}
		free_vm(&corewar);
	}
	else
		kill(COREWAR_USAGE);
	return (0);
}
