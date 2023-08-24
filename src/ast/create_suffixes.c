/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_suffixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:47:08 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_cmd_arg(t_llist *leaf_node)
{
	const t_token	*token = leaf_node->content;
	t_ntree			*new_leaf_content;
	t_llist			*new_leaf;

	new_leaf_content = leaf_new(token);
	if (new_leaf_content == NULL)
		return (NULL);
	new_leaf = llstnew(new_leaf_content);
	if (new_leaf == NULL)
		return (ast_free(new_leaf_content), NULL);
	return (ast_new(CMD_ARG, NULL, new_leaf));
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
		if (is_token_redirection(current->content))
		{
			next = llstnext(current, 2);
			new_child = create_child_range(current, next, create_redirection);
		}
		else
		{
			next = current->next;
			new_child = create_child(current, create_cmd_arg);
		}
		if (new_child == NULL)
			return (llstclear(&suffixes, ast_free), NULL);
		llstadd_back(&suffixes, new_child);
		current = next;
	}
	return (suffixes);
}
