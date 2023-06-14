/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:03:39 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 14:33:31 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	*llstmax(t_llist *llst, int (*comp)(void *, void *))
{
	t_llist	*current;
	void	*max;

	if (llst == NULL)
		return (NULL);
	max = current->content;
	current = llst;
	while (current != NULL)
	{
		if (comp(current->content, max) > 0)
			max = current->content;
		current = current->next;
	}
	return (max);
}
