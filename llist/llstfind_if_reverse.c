/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstfind_if_reverse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:25:50 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/19 12:56:54 by aguyon           ###   ########.fr       */
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
