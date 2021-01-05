/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/05 21:40:44 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			init_corewar(t_corewar **corewar)
{
	if (!(*corewar = (t_corewar*)malloc(sizeof(t_corewar))))
		return kill("Error on memory allocating");
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	(*corewar)->cycles = 0;
	(*corewar)->lives = 0;
	(*corewar)->cycles_to_die = CYCLE_TO_DIE;
	(*corewar)->checks = 0;
	(*corewar)->players_count = 0;
	(*corewar)->carrages_count = 0;
	set_operations((*corewar)->operations);
	return (1);
}

void		check(t_corewar **corewar)
{
	(*corewar)->checks++;
	die_carrages(corewar, (*corewar)->carrages, NULL, NULL);
	if ((*corewar)->lives >= NBR_LIVE || (*corewar)->checks == MAX_CHECKS)
	{
		(*corewar)->cycles_to_die -= CYCLE_DELTA;
		(*corewar)->checks = 0;
	}
	(*corewar)->lives = 0;
}

void		die_carrages(t_corewar **corewar, t_carrage *current,
	t_carrage *del, t_carrage *temp)
{
	while (current != NULL)
	{
		if ((*corewar)->cycles_to_die <= 0
			|| ((*corewar)->cycles - current->last_live_cycle) >= (*corewar)->cycles_to_die)
		{
			del = current;
			current = current->next;
			if ((*corewar)->carrages == del)
				(*corewar)->carrages = current;
			else
			{
				temp = (*corewar)->carrages;
				while (temp->next != del)
					temp = temp->next;
				temp->next = temp->next->next;
			}
			free(del);
			(*corewar)->carrages_count--;
		}
		else
			current = current->next;
	}
}

void		start_vm(t_corewar **corewar)
{
	mock_generator(corewar);
	init_arena(corewar);
	init_carrages(corewar);
	(*corewar)->champion_id = (*corewar)->carrages->player->id;
	intro_players(&(*corewar)->players);
	while ((*corewar)->carrages_count)
	{
		do_cycle(corewar);
		if ((*corewar)->cycles_to_die <= 0 ||
			((*corewar)->cycles % (*corewar)->cycles_to_die) == 0)
			check(corewar);
	}

}

void		do_cycle(t_corewar **corewar)
{
	t_carrage		*carrage;

	(*corewar)->cycles++;
	carrage = (*corewar)->carrages;
	while (carrage)
	{
		if (!carrage->wait_cycles)
		{
			carrage->op_code = (*corewar)->arena[carrage->pc];
			if (carrage->op_code >= 1 && carrage->op_code <= 16)
				carrage->wait_cycles = (*corewar)->operations[carrage->op_code - 1].cycles;
		}
		if (carrage->wait_cycles)
			carrage->wait_cycles--;
		if (!carrage->wait_cycles)
		{
			//exec op
		}
		carrage = carrage->next;
	}
}

void		intro_players(t_player **players)
{
	t_player *player;

	if (!players)
		return;
	ft_putendl("Introducing contestants...");
	player = (*players);
	while (player != NULL)
	{
		ft_putstr("* Player ");
		ft_putnbr(player->id);
		ft_putstr(", weighing ");
		ft_putnbr(player->size);
		ft_putstr(" bytes, \"");
		ft_putstr(player->name);
		ft_putstr("\" (\"");
		ft_putstr(player->comment);
		ft_putstr("\") !\n");
		player = player->next;
	}
}

void		mock_generator(t_corewar **corewar)
{
	t_player		*player;

	player = new_player(1, "batman", "I am help your city");
	player->code = (unsigned char *) "\x02\x90\x00\x00\x00\x00\x03\x09\x00\x50\x09\x00\x00\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x0B\x68\x01\xFF\xB6\x00\x01\x0B\x68\x01\xFF\xAF\x00\x0F\x0B\x68\x01\xFF\xA8\x00\x1D\x0B\x68\x01\xFF\xA1\x00\x2B\x0B\x68\x01\xFF\x9A\x00\x39\x0B\x68\x01\xFF\x93\x00\x47\x02\x90\x00\x06\x00\x00\x04\x02\x90\x00\x0E\x00\x00\x0C\x02\x90\x00\x00\x00\x01\x0B\x02\x90\x00\x00\x00\x06\x0A\x01\x00\x00\x00\x2A\x0B\x68\x04\xFF\x65\x00\x01\x04\x54\x04\x0C\x04\x05\x54\x0A\x0B\x0A\x09\xFF\xCE\x0C\xFF\xE7\x01\x00\x00\x00\x03\x0C\x00\x28\x01\x00\x00\x00\x04\x0C\x00\x45\x01\x00\x00\x00\x2A\x0A\xA4\x00\x08\xFF\x3F\x0F\x02\x90\xFF\xFF\xFF\x46\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFF\x24\x01\x00\x00\x00\x2A\x0C\x00\x3D\x01\x00\x00\x00\x2A\x0A\xA4\x00\x04\xFF\x1A\x0F\x02\x90\xFF\xFF\xFF\x42\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFE\xFF\x01\x00\x00\x00\x2A\x0A\xA4\x00\x0C\xFE\xFD\x0F\x02\x90\xFF\xFF\xFF\x4A\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFE\xE2\x01\x00\x00\x00\x2A\x0A\xA4\x00\x00\xFE\xE0\x0F\x02\x90\xFF\xFF\xFF\x3E\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFE\xC5";
	player->size = 375;
	(*corewar)->players_count++;
	(*corewar)->players = player;
	player = new_player(2, "ant man", "test desc");
	player->code = (unsigned char *) "\x03\x70\x01\x00\x13\x02\x90\x00\x00\x00\x00\x0F\x0C\x00\x06\x09\x01\x8C\x01\x00\x00\x00\x2A\x0C\x01\x84\x09\xFF\xF8\x01\x00\x00\x00\x2A\x0C\x00\x17\x03\x70\x01\x00\x0D\x02\x90\x00\x00\x00\x00\x0F\x01\x00\x00\x00\x2A\x09\xFF\xFB\x01\x00\x00\x00\x2A\x0C\x00\x17\x03\x70\x01\x00\x0D\x02\x90\x00\x00\x00\x00\x0F\x01\x00\x00\x00\x2A\x09\xFF\xFB\x01\x00\x00\x00\x2A\x0C\x00\x17\x03\x70\x01\x00\x0D\x02\x90\x00\x00\x00\x00\x0F\x01\x00\x00\x00\x2A\x09\xFF\xFB\x01\x00\x00\x00\x2A\x0C\xFF\xA7\x03\x70\x01\x00\x0D\x02\x90\x00\x00\x00\x00\x0F\x01\x00\x00\x00\x2A\x09\xFF\xFB\x01\x00\x00\x00\x2A\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x03\x70\x08\xFE\x70\x02\x90\x00\x00\x00\x00\x0F\x09\xFE\xF5\x01\x00\x00\x00\x2A\x0C\x00\x2B\x01\x00\x00\x00\x2A\x0C\x00\x52\x01\x00\x00\x00\x2A\x0C\x00\x78\x02\x90\x03\x70\x03\x00\x03\x02\x90\x13\x03\x70\x06\x06\x02\x90\x00\x00\x00\x00\x0F\x09\x00\x8A\x01\x00\x00\x00\x2A\x0C\xFF\xCB\x01\x00\x00\x00\x2A\x0C\xFE\x45\x02\x90\x0F\x03\x70\x06\x03\x02\x90\x17\x03\x70\x06\x06\x02\x90\x00\x00\x00\x00\x0F\x02\x90\x00\x00\x00\x00\x0F\x09\x00\x5B\x01\x00\x00\x00\x2A\x0C\xFE\x8E\x02\x90\xFF\xFF\x01\x42\x03\x02\x90\x1A\x03\x70\x06\x06\x02\x90\x00\x00\x00\x00\x0F\x02\x90\x00\x00\x00\x00\x0F\x02\x90\x00\x00\x00\x00\x0F\x09\x00\x2D\x03\x50\x01\x03\x02\x90\x0F\x03\x70\x06\x06\x02\x90\x00\x00\x00\x00\x0F\x02\x90\x00\x00\x00\x00\x0F\x02\x90\x00\x00\x00\x00\x0F\x02\x90\x00\x00\x00\x00\x0F\x09\x00\x03\x03\x70\x03\x00\x0F\x03\x70\x06\xFF\xFF\x01\x00\x00\x00\x2A";
	player->size = 682;
	(*corewar)->players_count++;
	add_player(&(*corewar)->players, player);
}
