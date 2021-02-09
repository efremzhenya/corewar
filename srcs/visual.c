/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:25:19 by lseema            #+#    #+#             */
/*   Updated: 2021/02/04 00:27:45 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	alloc_visual(t_corewar **corewar)
{
	int i;

	if (!((*corewar)->visual = (t_visual*)malloc(sizeof(t_visual))))
		err_allocate((*corewar)->visual);
	(*corewar)->visual->speed = 100;
	(*corewar)->visual->status = 1;
	(*corewar)->visual->debug_mode = 0;
	(*corewar)->visual->sound =
		(t_sound){.on = 1, .die = 0, .jump = 0, .win = 0, .clone = 0};
	i = 0;
	while (i < MEM_SIZE)
	{
		(*corewar)->visual->arena[i].code_owner = 0;
		(*corewar)->visual->arena[i].update = 0;
		(*corewar)->visual->arena[i].set = NULL;
		i++;
	}
}

void	init_visual(t_corewar **corewar)
{
	if (initscr() == NULL)
		terminate(ERR_VISUAL_ON_ALLOC);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	write(1, "\033[?1003h", 9);
	fflush(stdout);
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

void	end_visual(t_corewar **corewar)
{
	flushinp();
	timeout(-1);
	getch();
	write(1, "\033[?1000h", 9);
	fflush(stdout);
	delwin((*corewar)->visual->windows.arena);
	delwin((*corewar)->visual->windows.stats);
	endwin();
}
