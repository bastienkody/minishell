/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:09:32 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/04 11:19:02 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstmap(t_llist *llst, void *(*f)(void *), void (*del)(void *))
{
	t_llist	*new_llst;
	t_llist	*new_node;
	void	*new_content;

	new_llst = NULL;
	while (llst != NULL)
	{
		new_content = f(llst->content);
		if (new_content == NULL)
			return (llstclear(&new_llst, del), NULL);
		new_node = llstnew(new_content);
		if (new_node == NULL)
			return (llstclear(&new_llst, del), free(new_content), NULL);
		llstadd_back(&new_llst, new_node);
		llst = llst->next;
	}
	return (new_llst);
}
