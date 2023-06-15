/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextract_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:31:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 12:42:14 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

#include "llist.h"

t_llist	*llstextract(t_llist *begin, t_llist *end)
{
	t_llist	*prev;
	t_llist	*next;

	prev = begin->prev;
	next = end;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	begin->prev = NULL;
	end->next = NULL;
	return (begin);
}


1 2 3 4