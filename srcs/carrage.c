/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carrage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:27:32 by lseema            #+#    #+#             */
/*   Updated: 2021/01/02 19:47:50 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carrage		*new_carrage(size_t id)
{
	t_carrage	*carrage;
	int			i;

	if (!(carrage = (t_carrage *)malloc(sizeof(t_carrage))))
		return (NULL);
	carrage->id = id;
	carrage->cycle = 0;
	carrage->op_code = 0;
	carrage->pc = 0;
	carrage->next = NULL;
	i = 0;
	while(i < REG_NUMBER)
		carrage->registers[i++] = 0;
	return (carrage);
}

