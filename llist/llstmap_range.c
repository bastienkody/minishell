/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmap_range.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:41:00 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 21:41:06 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstmap_range(t_llist *begin, t_llist *end, void *(*f)(void *),
	void (*del)(void *))
{
	t_llist	*new_llst;
	t_llist	*new_node;
	t_llist	*current;

	new_llst = NULL;
	current = begin;
	while (current != end)
	{
		new_node = llstnew(f(current->content));
		if (new_node == NULL)
			return (llstclear(&new_llst, del), NULL);
		llstadd_back(&new_llst, new_node);
		current = current->next;
	}
	return (new_llst);
}
