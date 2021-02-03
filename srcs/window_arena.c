/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 23:45:28 by lseema            #+#    #+#             */
/*   Updated: 2021/02/01 23:46:11 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	draw_arena(t_corewar **corewar)
{
	int x;
	int y;
	int i;

	y = 0;
	x = 0;
	i = 0;
	if (!(*corewar)->visual->windows.arena)
		return ;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			y++;
			x = 1;
		}
		if ((*corewar)->visual->arena[i].update > 0 || (*corewar)->cycles == 0)
		{
			draw_code(corewar, y, x, i);
			(*corewar)->visual->arena[i].update = 0;
		}
		x += 3;
		i++;
	}
	wrefresh((*corewar)->visual->windows.arena);
}

void	draw_code(t_corewar **corewar, int y, int x, int i)
{
	char	*hex;

	color_on((*corewar)->visual->windows.arena, (*corewar)->visual->arena[i]);
	if (!(hex = dec_to_hex(read_byte((*corewar)->arena, i)))[1])
		mvwaddch((*corewar)->visual->windows.arena, y, x++, '0');
	mvwaddch((*corewar)->visual->windows.arena, y, x++, hex[0]);
	if (hex[1])
		mvwaddch((*corewar)->visual->windows.arena, y, x++, hex[1]);
	free(hex);
}

void	color_on(WINDOW *arena_window, t_arena_info arena)
{
	int	pair;

	if (arena.code_owner == 0)
		pair = arena.set == NULL ? STANDART : NOT_PLAYER_CARRAGE;
	else if (arena.set == NULL)
		pair = arena.code_owner;
	else
		pair = arena.code_owner + 6;
	wattron(arena_window, COLOR_PAIR(pair));
}
