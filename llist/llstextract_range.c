/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextract_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:31:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/26 18:22:43 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"
#include <stdio.h>

// t_llist	*llstextract_range(t_llist *begin, t_llist *end)
// {
// 	t_llist	*prev;
// 	t_llist	*next;

// 	prev = begin->prev;
// 	next = end;
// 	if (prev != NULL)
// 		prev->next = next;
// 	if (next != NULL)
// 		next->prev = prev;
// 	if (begin != NULL)
// 		begin->prev = NULL;
// 	if (end != NULL)
// 		end->next = NULL;
// 	return (begin);
// }

t_llist	*llstextract_range(t_llist **begin_llst, t_llist *begin, t_llist *end)
{
	t_llist	*new;
	t_llist	*next;

	new = NULL;

	while (begin != end)
	{
		next = begin->next;
		llstadd_back(&new, llstextractone(begin_llst, begin));
		begin = next;
	}
	return (new);
}
