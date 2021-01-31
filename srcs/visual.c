/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:25:19 by lseema            #+#    #+#             */
/*   Updated: 2021/01/31 17:16:08 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	init_visual(t_corewar **corewar)
{
	if (initscr() == NULL)
		terminate(ERR_VISUAL_ON_ALLOC);
	keypad(stdscr, true);
	curs_set(false);
	if (has_colors())
	{
		use_default_colors();
		start_color();
		init_pair(STANDART, COLOR_WHITE, COLOR_BLACK);
		init_players_colors(corewar);
	}
	init_windows(corewar);
	draw_arena(corewar);
	draw_info(corewar);
}

void	init_windows(t_corewar **corewar)
{
	if (!(*corewar)->visual->windows.arena)
	{
		(*corewar)->visual->windows.arena = subwin(stdscr,
			ARENA_WIN_HEIGTH, ARENA_WIN_WIDTH, ARENA_WIN_Y, ARENA_WIN_X);
		leaveok((*corewar)->visual->windows.arena, true);
		wbkgd((*corewar)->visual->windows.arena, COLOR_PAIR(5));
		box((*corewar)->visual->windows.arena, 0, 0);
		mvwprintw((*corewar)->visual->windows.arena, 0, 3, " MEMORY ");
	}
	if (!(*corewar)->visual->windows.stats)
	{
		(*corewar)->visual->windows.stats = subwin(stdscr,
			INFO_WIN_HEIGTH, INFO_WIN_WIDTH, INFO_WIN_Y, INFO_WIN_X);
		wbkgd((*corewar)->visual->windows.stats, COLOR_PAIR(5));
		leaveok((*corewar)->visual->windows.stats, true);
	}
}

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

void	init_players_colors(t_corewar **corewar)
{
	t_player	*player;

	player = (*corewar)->players;
	while (player)
	{
		init_pair(player->id, player->id + 8, COLOR_BLACK);
		player = player->next;
	}
	init_pair(PLAYER1_CARRAGE, LIGHT_RED, GREY);
	init_pair(PLAYER2_CARRAGE, LIGHT_GREEN, GREY);
	init_pair(PLAYER3_CARRAGE, LIGHT_YELLOW, GREY);
	init_pair(PLAYER4_CARRAGE, LIGHT_BLUE, GREY);
	init_pair(NOT_PLAYER_CARRAGE, COLOR_WHITE, GREY - 2);
}
