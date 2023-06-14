/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:09:32 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 23:49:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstmap(t_llist *llst, void *(*f)(void *), void (*del)(void *))
{
	t_llist	*new_llst;
	t_llist	*new_node;

	new_llst = NULL;
	while (llst != NULL)
	{
		new_node = llstnew(f(llst->content));
		if (new_node == NULL)
			return (llstclear(&new_llst, del), NULL);
		llstadd_back(&llst, new_node);
		llst = llst->next;
	}
	return (new_llst);
}
