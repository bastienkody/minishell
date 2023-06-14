/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstncomp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:27:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 15:00:41 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

int	llstncomp(t_llist *llst1, t_llist *llst2, size_t n,
	int (*comp)(void *, void *))
{
	t_llist	*current1;
	t_llist	*current2;
	int		diff;
	size_t	i;

	i = 0;
	while (current1 != NULL && current2 != NULL && i < n)
	{
		diff = comp(current1->content, current2->content);
		if (diff != 0)
			return (diff);
		current1 = current1->next;
		current2 = current2->next;
	}
	return (comp(current1->content, current2->content));
}
