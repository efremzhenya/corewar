/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/01/08 20:20:29 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			init_corewar(t_corewar **corewar)
{
	if (!(*corewar = (t_corewar*)malloc(sizeof(t_corewar))))
		return kill("Error on memory allocating");
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	(*corewar)->cw_args = NULL;
	(*corewar)->cycles = 0;
	(*corewar)->lives = 0;
	(*corewar)->cycles_to_die = CYCLE_TO_DIE;
	(*corewar)->checks = 0;
	(*corewar)->players_count = 0;
	(*corewar)->carrages_count = 0;
	return (1);
}

void		start_vm(t_corewar **corewar)
{
	t_op	operations[OP_COUNT];

	mock_generator(corewar);
	init_arena(corewar);
	init_carrages(corewar);
	set_operations(operations);
	(*corewar)->winner = (*corewar)->carrages->player->id;
	intro_message(&(*corewar)->players);
	while ((*corewar)->carrages_count)
	{
		(*corewar)->cycles++;
		carrages_exec(corewar, operations);
		if ((*corewar)->cycles_to_die <= 0 ||
			((*corewar)->cycles % (*corewar)->cycles_to_die) == 0)
			check(corewar);
	}
	winner_message(corewar);
}

void		carrages_exec(t_corewar **corewar, t_op *op)
{
	t_carrage		*carrage;
	int				offset;

	carrage = (*corewar)->carrages;
	while (carrage)
	{
		if (!carrage->wait_cycles)
		{
			carrage->op_code = read_byte((*corewar)->arena, carrage->pc);
			if (carrage->op_code > 0 && carrage->op_code < OP_COUNT)
				carrage->wait_cycles = op[carrage->op_code].cycles;
		}
		if (carrage->wait_cycles)
			carrage->wait_cycles--;
		if (!carrage->wait_cycles)
		{
			if (carrage->op_code > 0 && carrage->op_code < OP_COUNT)
			{
				carrage->is_half_size_dir = op[carrage->op_code].is_half_size_dir;
				if ((offset = (chk_arg_type(op[carrage->op_code], carrage, (*corewar)->arena))))
					op[carrage->op_code].f(corewar, carrage);
				else
					offset = instruction_size(carrage, op[carrage->op_code]);
			}
			else
				offset = 1;
			if ((carrage->pc = (carrage->pc + offset)) >= MEM_SIZE)
				carrage->pc = carrage->pc - MEM_SIZE;
		}
		carrage = carrage->next;
	}
}

 void		mock_generator(t_corewar **corewar)
 {
 	t_player		*player;
	char			**args;
	int				ac[1];

	args = (char**)malloc(sizeof(char*));
	ac[0] = 0;
	*args = ft_strdup("batman");
 	player = new_player(ac, args, corewar, 1);
	player->comment = "description";
 	player->code = (unsigned char *) "\x02\x90\x00\x00\x00\x00\x03\x09\x00\x50\x09\x00\x00\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x01\x00\x00\x00\x2A\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x0B\x64\x0F\x00\x00\x0E\x09\xFF\x38\x0B\x68\x01\xFF\xB6\x00\x01\x0B\x68\x01\xFF\xAF\x00\x0F\x0B\x68\x01\xFF\xA8\x00\x1D\x0B\x68\x01\xFF\xA1\x00\x2B\x0B\x68\x01\xFF\x9A\x00\x39\x0B\x68\x01\xFF\x93\x00\x47\x02\x90\x00\x06\x00\x00\x04\x02\x90\x00\x0E\x00\x00\x0C\x02\x90\x00\x00\x00\x01\x0B\x02\x90\x00\x00\x00\x06\x0A\x01\x00\x00\x00\x2A\x0B\x68\x04\xFF\x65\x00\x01\x04\x54\x04\x0C\x04\x05\x54\x0A\x0B\x0A\x09\xFF\xCE\x0C\xFF\xE7\x01\x00\x00\x00\x03\x0C\x00\x28\x01\x00\x00\x00\x04\x0C\x00\x45\x01\x00\x00\x00\x2A\x0A\xA4\x00\x08\xFF\x3F\x0F\x02\x90\xFF\xFF\xFF\x46\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFF\x24\x01\x00\x00\x00\x2A\x0C\x00\x3D\x01\x00\x00\x00\x2A\x0A\xA4\x00\x04\xFF\x1A\x0F\x02\x90\xFF\xFF\xFF\x42\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFE\xFF\x01\x00\x00\x00\x2A\x0A\xA4\x00\x0C\xFE\xFD\x0F\x02\x90\xFF\xFF\xFF\x4A\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFE\xE2\x01\x00\x00\x00\x2A\x0A\xA4\x00\x00\xFE\xE0\x0F\x02\x90\xFF\xFF\xFF\x3E\x0E\x02\x90\x00\x00\x00\x00\x02\x09\xFE\xC5";
 	player->size = 375;
 	(*corewar)->players_count++;
 	(*corewar)->players = player;
}
