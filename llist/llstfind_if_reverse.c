/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstfind_if_reverse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:25:50 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 17:40:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstfind_if_reverse(const t_llist *llst, int (*p)(void *))
{
	const t_llist	*last = llstlast(llst);

	while (last != NULL)
	{
		if (p(last->content))
			return ((t_llist *)last);
		last = last->prev;
	}
	return (NULL);
}

t_llist	*llstfind_if_reverse_range(const t_llist *rbegin, const t_llist *rend, int (*p)(void *))
{
	const t_llist	*current;

	current = rend;
	while (current != NULL && current != rbegin)
	{
		if (p(current->content))
			return ((t_llist *)current);
		current = current->prev;
	}
	return (NULL);
}