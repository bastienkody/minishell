/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:06:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 15:18:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	*llstmin(t_llist *llst, int (*comp)(void *, void *))
{
	t_llist	*current;
	void	*min;

	if (llst == NULL)
		return (NULL);
	min = llst->content;
	current = llst->next;
	while (current != NULL)
	{
		if (comp(current->content, min) < 0)
			min = current->content;
		current = current->next;
	}
	return (min);
}
