/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstall_of.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:56:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 14:33:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

int	llstall_of(t_llist *llst, int (*p)(void *))
{
	t_llist	*current;

	current = llst;
	while (current != llst)
	{
		if (!p(current->content))
			return (0);
		current = current->next;
	}
	return (1);
}
