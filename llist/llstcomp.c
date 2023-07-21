/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstcomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:14:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 18:34:03 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

int	llstcomp(t_llist *llst1, t_llist *llst2, int (*comp)(void *, void *))
{
	t_llist	*current1;
	t_llist	*current2;
	int		diff;

	current1 = llst1;
	current2 = llst2;
	while (current1 != NULL && current2 != NULL)
	{
		diff = comp(current1->content, current2->content);
		if (diff != 0)
			return (diff);
		current1 = current1->next;
		current2 = current2->next;
	}
	if (current1 == NULL && current2 == NULL)
		return (0);
	if (current1 == NULL && current2 != NULL)
		return (1);
	if (current1 != NULL && current2 == NULL)
		return (-1);
	return (comp(current1->content, current2->content));
}
