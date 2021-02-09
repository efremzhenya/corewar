/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 23:43:10 by lseema            #+#    #+#             */
/*   Updated: 2021/02/03 22:51:19 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void		draw_info(t_corewar **corewar)
{
	int x;
	int y;

	y = 0;
	x = 3;
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Status: %s", (*corewar)->carrages_count ? "play" : "stoped");
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Carrages: %i", (*corewar)->carrages_count);
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Cycles: %d", (*corewar)->cycles);
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Cycles before check: %d/%d", (ssize_t)(*corewar)->cycles - (*corewar)->last_check_cycle ,(*corewar)->cycles_to_die);
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Lives current period: %d/%d", (*corewar)->lives, NBR_LIVE);
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Ineffective checks: %d/%d", (*corewar)->checks, MAX_CHECKS);
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	y = draw_players(&(*corewar), y, x);
	wmove((*corewar)->visual->windows.stats, y += 2, x);
	wclrtoeol((*corewar)->visual->windows.stats);
	mvwprintw((*corewar)->visual->windows.stats, y, x, "Speed: %i", (*corewar)->visual->speed);

	box((*corewar)->visual->windows.stats, 0, 0);
	mvwprintw((*corewar)->visual->windows.stats, 0, 3, " INFO ");
	wrefresh((*corewar)->visual->windows.stats);
}

int		draw_players(t_corewar **corewar, int y, int x)
{
	t_player	*player;
	WINDOW		*stats_win;
	char		*res;

	stats_win = (*corewar)->visual->windows.stats;
	player = (*corewar)->players;
	res = !(*corewar)->carrages_count ? "WIN" : "LIVE";
	if (!(*corewar)->carrages_count)
		(*corewar)->visual->sound.win = 1;
	while (player)
	{
		wattron(stats_win, COLOR_PAIR(player->id));
		wmove(stats_win, y, x);
		wclrtoeol(stats_win);
		mvwprintw(stats_win, y++, x, "Player: %i: %s  %s", player->id,
			player->name, (*corewar)->winner == player->id ? res : "");
		y = draw_comment(corewar, player->comment, y, x + 2);
		player = player->next;
	}
	wattron(stats_win, COLOR_PAIR(STANDART));
	return (y);
}

int		draw_comment(t_corewar **corewar, char *comment, int y, int x)
{
	int		i;
	int		len;
	int		per_line;
	char	*sub_comnt;

	wattron((*corewar)->visual->windows.stats, COLOR_PAIR(STANDART));
	if ((len = ft_strlen(comment)) == 0)
		return (y);
	per_line = INFO_WIN_WIDTH - x - 1;
	i = 0;
	while (i < (len / per_line + (!!(len % (per_line)))))
	{
		if (!(*corewar)->cycles)
		{
			wmove((*corewar)->visual->windows.stats, y, x);
			wclrtoeol((*corewar)->visual->windows.stats);
			sub_comnt = ft_strsub(comment, per_line * i, per_line);
			mvwprintw((*corewar)->visual->windows.stats, y, x, "%s", sub_comnt);
			free(sub_comnt);
		}
		i++;
		y++;
	}
	return (y++);
}
