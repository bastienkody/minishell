/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstrange_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:14:51 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 16:09:02 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstrange_remove(t_llist *begin, t_llist *end, void (*del)(void *))
{
	t_llist	*current;
	t_llist	*next;

	current = begin;
	while (current != NULL && current != end)
	{
		next = current->next;
		llstremoveone(&current, del);
		current = next;
	}
}
