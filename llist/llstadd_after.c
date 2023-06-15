/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstadd_after.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:24:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 15:01:52 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstadd_after(t_llist **llst, t_llist *new)
{
	t_llist	*next;

	if (*llst == NULL)
		*llst = new;
	else
	{
		next = (*llst)->next;
		if (next != NULL)
			next->prev = new;
		new->prev = *llst;
		new->next = next;
		(*llst)->next = new;
	}
}
