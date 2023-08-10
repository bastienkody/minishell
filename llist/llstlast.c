/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstlast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:23:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 10:36:13 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstlast(const t_llist *llst)
{
	if (llst == NULL || llst->next == NULL)
		return ((t_llist *)llst);
	return (llstlast(llst->next));
}

t_llist	*llstlast_range(const t_llist *begin, const t_llist *end)
{
	if (begin == NULL)
		return ((t_llist *)NULL);
	if (end == NULL)
		return (llstlast(begin));
	else
		return (end->prev);
}
