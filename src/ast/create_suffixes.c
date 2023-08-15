/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_suffixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 17:13:34 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_cmd_arg(t_llist	*leaf_node)
{
	t_llist	*new_leaf_node;

	new_leaf_node = leaf_node_dup(leaf_node);
	if (new_leaf_node == NULL)
		return (NULL);
	return (ast_new(CMD_ARG, NULL, new_leaf_node));
}

t_llist	*create_suffixes(t_llist *begin, t_llist *end)
{
	t_llist	*suffixes;
	t_llist	*new_child;
	t_llist	*current;
	t_llist	*next;

	suffixes = NULL;
	current = begin;
	while (current != NULL && current != end)
	{
		if (is_node_redirection(current->content))
		{
			next = llstnext(current, 2);
			new_child = create_child_range(current, next, create_redirection);
		}
		else if (is_node_word(current->content))
		{
			next = current->next;
			new_child = create_child(current, create_cmd_arg);
		}
		else
			new_child = NULL;
		if (new_child == NULL)
			return (llstclear(&suffixes, ast_free), NULL);
		llstadd_back(&suffixes, new_child);
		current = next;
	}
	return (suffixes);
}
