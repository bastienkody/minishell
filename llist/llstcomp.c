/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstcomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:14:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 15:17:29 by aguyon           ###   ########.fr       */
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
	return (comp(current1->content, current2->content));
}
