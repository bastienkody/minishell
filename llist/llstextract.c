/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 23:55:16 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 00:06:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstextract(t_llist **llst)
{
	t_llist	*prev;
	t_llist	*next;

	prev = (*llst)->prev;
	next = (*llst)->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	else
		*llst = (t_llist){(*llst)->content, NULL, NULL};
	return (llst);
}
