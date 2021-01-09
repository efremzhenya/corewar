/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:05:57 by lseema            #+#    #+#             */
/*   Updated: 2021/01/08 20:16:26 by lseema           ###   ########.fr       */
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
