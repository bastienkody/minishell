/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremoveone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:18:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 10:30:29 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremoveone(t_llist **llst, void (*del)(void *))
{
	t_llist	*prev;
	t_llist	*next;

	if (*llst == NULL)
		return ;
	prev = (*llst)->prev;
	next = (*llst)->next;
	llstdelone(*llst, del);
	if (prev != NULL)
		prev->next = next;
	else
		*llst = next;
	if (next != NULL)
		next->prev = prev;
}
