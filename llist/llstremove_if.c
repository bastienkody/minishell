/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremove_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:00:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 10:07:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremove_if(t_llist **llst, int (*p)(void *), void (*del)(void *))
{
	t_llist	*current;
	t_llist	*next;

	current = *llst;
	while (current != NULL)
	{
		next = current->next;
		if (p(current->content))
			llstremoveone(llst, current, del);
		current = next;
	}
}