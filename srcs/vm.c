/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:00:45 by lseema            #+#    #+#             */
/*   Updated: 2021/02/13 21:02:35 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

int			init_corewar(t_corewar **corewar)
{
	*corewar = (t_corewar*)malloc(sizeof(t_corewar));
	err_allocate(*corewar);
	(*corewar)->players = NULL;
	(*corewar)->carrages = NULL;
	(*corewar)->cycles = 0;
	(*corewar)->lives = 0;
	(*corewar)->cycles_to_die = CYCLE_TO_DIE;
	(*corewar)->checks = 0;
	(*corewar)->players_count = 0;
	(*corewar)->carrages_count = 0;
	(*corewar)->last_check_cycle = 0;
	(*corewar)->cw_args = (t_arg *)malloc(sizeof(t_arg));
	err_allocate((*corewar)->cw_args);
	(*corewar)->cw_args->dump = -1;
	(*corewar)->cw_args->n_pl = -1;
	(*corewar)->cw_args->visual = 0;
	(*corewar)->visual = NULL;
	ft_bzero((*corewar)->arena, sizeof((*corewar)->arena));
	return (1);
}

void		start_vm(t_corewar **corewar)
{
	t_op		operations[OP_COUNT];

	init_vm(corewar);
	set_operations(operations);
	while ((*corewar)->carrages_count)
	{
		if (!(*corewar)->cw_args->visual || (*corewar)->visual->status)
		{
			(*corewar)->cycles++;
			carrages_exec(corewar, operations);
			if ((*corewar)->cycles_to_die <= 0 ||
				((ssize_t)((*corewar)->cycles - (*corewar)->last_check_cycle))
					== (*corewar)->cycles_to_die)
				check(corewar);
			if ((*corewar)->cw_args->dump > 0
				&& (*corewar)->cycles == (size_t)(*corewar)->cw_args->dump)
				dump((*corewar)->arena, 0, 0, NULL);
		}
		if ((*corewar)->cw_args->visual)
		{
			draw_arena(corewar);
			draw_info(corewar);
			delay_cycle((*corewar)->visual);
		}
	}
}

void		carrages_exec(t_corewar **corewar, t_op *op)
{
	t_carrage		*carrage;

	carrage = (*corewar)->carrages;
	while (carrage)
	{
		if (!carrage->wait_cycles)
		{
			carrage->op_code = read_byte((*corewar)->arena, carrage->pc);
			if (!(carrage->op_code > 0 && carrage->op_code < OP_COUNT))
				carrage->op_code = 0;
			carrage->wait_cycles = op[carrage->op_code].cycles;
		}
		if (carrage->wait_cycles)
			carrage->wait_cycles--;
		if (!carrage->wait_cycles)
		{
			exec_operation(corewar, carrage, op);
		}
		carrage = carrage->next;
	}
}

void		exec_operation(t_corewar **corewar, t_carrage *carrage, t_op *op)
{
	int				offset;
	int				old_pc;

	old_pc = carrage->pc;
	carrage->is_half_size_dir = op[carrage->op_code].is_half_size_dir;
	if ((offset = chk_arg_type(op[carrage->op_code], carrage,
		(*corewar)->arena)))
		op[carrage->op_code].f(corewar, carrage);
	else
		offset = instruction_size(carrage, op[carrage->op_code]);
	if (!carrage->carry || carrage->op_code != 0x09)
		carrage->pc = normalize_pc((carrage->pc + offset));
	if ((*corewar)->cw_args->visual)
	{
		remove_in_set(&(*corewar)->visual->arena[old_pc].set, carrage);
		(*corewar)->visual->arena[old_pc].update = 1;
		add_to_set(&(*corewar)->visual->arena[carrage->pc].set,
			new_set_elem(carrage));
		(*corewar)->visual->arena[carrage->pc].update = 1;
	}
}

void		init_vm(t_corewar **corewar)
{
	if ((*corewar)->cw_args->visual)
		alloc_visual(corewar);
	init_arena(corewar);
	init_carrages(corewar);
	(*corewar)->winner = (*corewar)->carrages->player->id;
	if ((*corewar)->cw_args->visual)
		init_visual(corewar);
	else
	{
		intro_message(&(*corewar)->players);
		if (!(*corewar)->cw_args->dump)
			dump((*corewar)->arena, 0, 0, NULL);
	}
}
