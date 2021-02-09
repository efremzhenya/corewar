/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:29:47 by lseema            #+#    #+#             */
/*   Updated: 2021/02/09 23:38:38 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>

/*
** COLORS
*/
# define GREY				250
# define LIGHT_RED			196
# define LIGHT_GREEN		22
# define LIGHT_YELLOW		229
# define LIGHT_BLUE			4

/*
** Palette SETS (text color and background color)
*/

# define PLAYER1			1
# define PLAYER2			2
# define PLAYER3			3
# define PLAYER4			4
# define STANDART			5
# define PLAYER1_CARRAGE	7
# define PLAYER2_CARRAGE	8
# define PLAYER3_CARRAGE	9
# define PLAYER4_CARRAGE 	10
# define NOT_PLAYER_CARRAGE	11

/*
** WINDOWS settings
*/

# define BYTE_PER_LINE 		64
# define CODE_LENGTH		3
# define ARENA_WIN_Y		0
# define ARENA_WIN_X		0
# define ARENA_WIN_HEIGTH	MEM_SIZE / BYTE_PER_LINE + 2
# define ARENA_WIN_WIDTH	BYTE_PER_LINE * CODE_LENGTH + 1
# define INFO_WIN_Y			0
# define INFO_WIN_X			ARENA_WIN_WIDTH + 3
# define INFO_WIN_HEIGTH	50
# define INFO_WIN_WIDTH		80

typedef struct				s_carrage_set
{
	struct s_carrage		*carrage;
	struct s_carrage_set	*next_in_set;
}							t_carrage_set;

typedef struct				s_arena_info
{
	unsigned char			code_owner:3;
	unsigned char			update:1;
	t_carrage_set			*set;
}							t_arena_info;

typedef struct				s_windows
{
	WINDOW					*arena;
	WINDOW					*stats;
}							t_windows;

typedef struct				s_sound
{
	unsigned int			on:1;
	unsigned int			die:1;
	unsigned int			jump:1;
	unsigned int			clone:1;
	unsigned int			win:1;
}							t_sound;

typedef struct				s_visual
{
	t_arena_info			arena[MEM_SIZE];
	t_windows				windows;
	t_sound					sound;
	unsigned short			speed;
	unsigned int			status:1;
	unsigned int			debug_mode:1;
}							t_visual;

/*
** Visual
*/

void						alloc_visual(t_corewar **corewar);
void						init_visual(t_corewar **corewar);
void						init_windows(t_corewar **corewar);
void						init_players_colors(t_corewar **corewar);
void						color_on(WINDOW *arena_window, t_arena_info arena);
void						draw_arena(t_corewar **corewar);
void						draw_info(t_corewar **corewar);
void						draw_code(t_corewar **corewar, int y, int x, int i);
void						end_visual(t_corewar **corewar);
void						delay_cycle(t_visual *visual);
int							draw_players(t_corewar **corewar, int y, int x);
int							draw_comment(t_corewar **corewar, char *comment,
	int y, int x);
int							draw_general_info(WINDOW *stats_win, int y, int x,
	t_corewar **corewar);
int							draw_additional_info(WINDOW *stats_win, int y,
	int x, t_corewar **corewar);

/*
** Visual events
*/

void						delay_cycle(t_visual *visual);
void						key_handler(t_visual *visual);

/*
** Sounds
*/

void						sound(t_visual *visual);
void						sound_die();
void						sound_win();
void						sound_jump();
void						sound_clone();

/*
** Visual carrage sets
*/

t_carrage_set				*new_set_elem(t_carrage *carrage);
int							add_to_set(t_carrage_set **set,
	t_carrage_set *elem);
int							is_contain_in_set(t_carrage_set **set,
	t_carrage *carrage);
void						free_set(t_carrage_set **set);
void						remove_in_set(t_carrage_set **set, t_carrage *elem);

#endif
