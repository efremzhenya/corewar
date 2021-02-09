/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:42:42 by lseema            #+#    #+#             */
/*   Updated: 2021/02/04 00:07:27 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	key_handler(t_visual *visual)
{
	MEVENT	event;
	int		ch;

	event = (MEVENT){.id = 0, .bstate = 0, .x = 0, .y = 0, .z = 0};
	timeout(0);
	ch = getch();
	if (ch != ERR)
	{
		if (ch == KEY_UP)
			visual->speed += (visual->speed >= 500 ? 0 : 5);
		else if (ch == KEY_DOWN)
			visual->speed -= (visual->speed <= 0 ? 0 : 5);
		if (ch == ' ')
			visual->status = !visual->status;
		if (ch == 's')
			visual->sound.on = !visual->sound.on;
		debug_keyboard(visual, ch, event);
		wrefresh(visual->windows.stats);
	}
}

void	debug_keyboard(t_visual *visual, int ch, MEVENT event)
{
	if (ch == 'd')
	{
		visual->debug_mode = !visual->debug_mode;
		move(ARENA_WIN_HEIGTH + 3, 0);
		clrtoeol();
		move(ARENA_WIN_HEIGTH + 4, 0);
		clrtoeol();
		move(ARENA_WIN_HEIGTH + 5, 0);
		clrtoeol();
		move(ARENA_WIN_HEIGTH + 6, 0);
		clrtoeol();
	}
	if (visual->debug_mode)
	{
		move(ARENA_WIN_HEIGTH+3, 0);
		clrtoeol();
		mvprintw(ARENA_WIN_HEIGTH+3, 0, "Key: %i", ch);
		if (ch == 409)
		{
			if (getmouse(&event) == OK)
			{
				move(ARENA_WIN_HEIGTH+4, 0);
				clrtoeol();
				move(ARENA_WIN_HEIGTH+5, 0);
				clrtoeol();
				move(ARENA_WIN_HEIGTH+6, 0);
				clrtoeol();
				mvprintw(ARENA_WIN_HEIGTH+4, 0, "Mouse x: %i", event.x);
				mvprintw(ARENA_WIN_HEIGTH+5, 0, "Mouse y: %i", event.y);
				mvprintw(ARENA_WIN_HEIGTH+6, 0, "Mouse state: %i", event.bstate);
			}
		}
	}
}

int		mouse_coord_to_pos(int x, int y)
{
	if (x > 0 && y > 0 && y < 65 && x < 192 && !(x % 3))
		return ((x / 3 + 1) * y - 1);
	return(0);
}

void	delay_cycle(t_visual *visual)
{
	int		i;

	if (visual->status)
	{
		i = visual->speed;
		while (i--)
		{
			delay_output(1);
			key_handler(visual);
		}
	}
	key_handler(visual);
	sound(visual);
}
