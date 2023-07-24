/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:03:39 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/24 13:46:43 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	*llstmax(t_llist *llst, int (*comp)(void *, void *))
{
	t_llist	*current;
	void	*max;

	if (llst == NULL)
		return (NULL);
	max = llst->content;
	current = llst->next;
	while (current != NULL)
	{
		if (comp(current->content, max) > 0)
			max = current->content;
		current = current->next;
	}
	return (max);
}
