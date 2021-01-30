/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:43:25 by lseema            #+#    #+#             */
/*   Updated: 2021/01/31 01:24:48 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

t_carrage_set	*new_set_elem(t_carrage *carrage)
{
	t_carrage_set *set;

	if (!(set = (t_carrage_set *)malloc(sizeof(t_carrage_set))))
		err_allocate(set);
	set->carrage = carrage;
	set->next_in_set = NULL;
	return (set);
}

int				add_to_set(t_carrage_set **set, t_carrage_set *elem)
{
	t_carrage_set	*tail;

	if (!set || !elem)
		return (0);
	if (is_contain_in_set(set, elem->carrage))
		return (0);
	if (!*set)
	{
		*set = elem;
		return (1);
	}
	tail = *set;
	while (tail && tail->next_in_set)
		tail = tail->next_in_set;
	tail->next_in_set = elem;
	elem->next_in_set = NULL;
	return (1);
}

int				is_contain_in_set(t_carrage_set **set, t_carrage *carrage)
{
	t_carrage_set *tail;

	if (!*set)
		return (0);
	tail = *set;
	while (tail->next_in_set)
	{
		if (tail->carrage == carrage)
			return (1);
		tail = tail->next_in_set;
	}
	return (tail->carrage == carrage);
}

void			free_set(t_carrage_set **set)
{
	t_carrage_set	*tail;
	t_carrage_set	*tmp;

	if (!set || !*set)
		return ;
	tail = *set;
	while (tail->next_in_set)
	{
		tmp = tail;
		tail = tail->next_in_set;
		free(tmp);
	}
	free(tail);
}

void			remove_in_set(t_carrage_set **set, t_carrage *elem)
{
	t_carrage_set *temp;
	t_carrage_set *prev;

	if (!*set || !elem)
		return ;
	temp = *set;
	if ((*set)->carrage == elem)
	{
		*set = (*set)->next_in_set;
		free(temp);
		return ;
	}
	while (temp != NULL && temp->carrage != elem)
	{
		prev = temp;
		temp = temp->next_in_set;
	}
	if (temp == NULL)
		return ;
	prev->next_in_set = temp->next_in_set;
	free(temp);
}
