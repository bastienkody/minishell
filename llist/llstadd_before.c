/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstadd_before.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:33:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 23:47:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstadd_before(t_llist	**llst, t_llist	*new)
{
	t_llist	*prev;
	t_llist	*temp;

	if (llst == NULL)
		*llst = new;
	else
	{
		temp = *llst;
		prev = (*llst)->prev;
		if (prev != NULL)
			prev->next = new;
		new->next = temp;
		new->prev = prev;
		temp->prev = new;
	}
}
