/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:42:42 by lseema            #+#    #+#             */
/*   Updated: 2021/02/09 23:37:56 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	key_handler(t_visual *visual)
{
	int		ch;

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
		wrefresh(visual->windows.stats);
	}
}

int		mouse_coord_to_pos(int x, int y)
{
	if (x > 0 && y > 0 && y < 65 && x < 192 && !(x % 3))
		return ((x / 3 + 1) * y - 1);
	return (0);
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
