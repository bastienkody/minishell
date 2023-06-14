/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremove_range.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:41:11 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 23:59:13 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremove_range(t_llist **begin, t_llist *end, void (*del)(void *))
{
	t_llist	*current;
	t_llist	*prev;
	t_llist	*next;

	(void)prev;
	(void)del;
	current = *begin;
	while (current != NULL && current != end)
	{
		prev = current->prev;
		next = current->next;
		current = next;
	}
}
