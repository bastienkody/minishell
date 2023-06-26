/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextractone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:29:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/23 15:29:24 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstextractone(t_llist **begin, t_llist *llst)
{
	t_llist	*prev;
	t_llist	*next;

	if (*begin == NULL || llst == NULL)
		return (NULL);
	if (llst->prev == NULL && llst->next == NULL)
		*begin = NULL;
	else
	{
		prev = llst->prev;
		next = llst->next;
		if (prev != NULL)
			prev->next = next;
		if (next != NULL)
			next->prev = prev;
	}
	return (llst);
}