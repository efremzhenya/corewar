/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:44:15 by lseema            #+#    #+#             */
/*   Updated: 2021/02/09 23:18:40 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void	sound(t_visual *visual)
{
	if (visual->sound.on)
	{
		if (visual->sound.win)
			sound_win();
		else if (visual->sound.die)
			sound_die();
		else if (visual->sound.clone && visual->speed >= 400)
			sound_clone();
		else if (visual->sound.jump && visual->speed >= 400)
			sound_jump();
		visual->sound =
			(t_sound){.on = 1, .clone = 0, .die = 0, .jump = 0, .win = 0};
	}
}

void	sound_die(void)
{
	system("pkill afplay");
	system("afplay resources/crush.wav &> /dev/null &");
}

void	sound_win(void)
{
	system("pkill afplay");
	system("afplay resources/ta_da.wav &> /dev/null &");
}

void	sound_jump(void)
{
	system("afplay resources/jump.wav &> /dev/null &");
}

void	sound_clone(void)
{
	system("afplay resources/baby_chicken.wav &> /dev/null &");
}
