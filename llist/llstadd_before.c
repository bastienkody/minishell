/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstadd_before.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:33:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 18:51:20 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstadd_before(t_llist	**llst, t_llist	*new)
{
	t_llist	*prev;

	if (llst == NULL)
		*llst = new;
	else
	{
		prev = (*llst)->prev;
		if (prev != NULL)
			prev->next = new;
		new->prev = prev;
		new->next = *llst;
		(*llst)->prev = new;
	}
}