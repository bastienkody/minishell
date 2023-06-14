/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremoveone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:18:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 23:59:29 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremoveone(t_llist **llst, void (*del)(void *))
{
	t_llist	*prev;
	t_llist	*next;

	prev = (*llst)->prev;
	next = (*llst)->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	llstdelone(*llst, del);
}


