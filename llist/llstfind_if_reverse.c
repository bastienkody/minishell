/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstfind_if_reverse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:25:50 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 23:22:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstfind_if_reverse(t_llist *llst, int (*p)(void *))
{
	const t_llist	*last = llstlast(llst);

	while (last != NULL)
	{
		if (p(last->content))
			return (last);
		last = last->prev;
	}
	return (NULL);
}
