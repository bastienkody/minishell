/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextract_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:31:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 17:13:42 by aguyon           ###   ########.fr       */
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

t_llist	*llstextract_range(t_llist *begin, t_llist *end)
{
	t_llist	*prev;
	t_llist	*next;
	t_llist	*new_end;

	prev = begin->prev;
	if (end == NULL)
	{
		if (prev != NULL)
			prev->next = NULL;
		(*begin).prev = NULL;
	}
	else
	{
		next = end;
		new_end = next->prev;
		if (prev != NULL)
			prev->next = next;
		next->prev = prev;
		new_end->next = NULL;
		(*begin).prev = NULL;
	}
	return (begin);
}
