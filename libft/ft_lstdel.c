/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:07:57 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:07:57 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cur;

	if (!del || !alst)
		return ;
	cur = *alst;
	while (cur != NULL)
	{
		del(cur->content, cur->content_size);
		free(cur);
		cur = cur->next;
	}
	*alst = NULL;
}
