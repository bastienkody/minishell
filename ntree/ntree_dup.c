/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:36:08 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 17:15:40 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ntree.h"

t_ntree	*ntree_dup(t_ntree *ntree, void *(*dup)(void *), void (*del)(void *));

static void	free_new_children(t_llist **children, void (*del)(void *))
{
	t_llist	*current;
	t_llist	*next;

	current = *children;
	while (current != NULL)
	{
		next = current->next;
		ntree_free((t_ntree **)&(current->content), del);
		free(current);
		current = next;
	}
	*children = NULL;
}

static t_llist	*children_dup(t_llist *children, void *(*dup)(void *),
	void (*del)(void *))
{
	t_llist	*new_children;
	t_ntree	*new_ntree;
	t_llist	*new_node;
	t_llist	*current;

	new_children = NULL;
	current = children;
	while (current != NULL)
	{
		new_ntree = ntree_dup(current->content, dup, del);
		if (new_ntree == NULL)
			return (free_new_children(&new_children, del), NULL);
		new_node = llstnew(new_ntree);
		if (new_node == NULL)
			return (free_new_children(&new_children, del),
				ntree_free(&new_ntree, del), NULL);
		llstadd_back(&new_children, new_node);
		current = current->next;
	}
	return (new_children);
}

t_ntree	*ntree_dup(t_ntree *ntree, void *(*dup)(void *), void (*del)(void *))
{
	t_llist	*new_children;
	void	*new_data;

	new_data = dup(ntree->data);
	if (new_data == NULL)
		return (NULL);
	if (ntree->children == NULL)
		new_children = NULL;
	else
	{
		new_children = children_dup(ntree->children, dup, del);
		if (new_children == NULL)
			return (del(new_data), NULL);
	}
	return (ntree_new(new_data, new_children));
}
