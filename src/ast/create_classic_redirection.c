/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_classic_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:10:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 16:48:03 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_operator(t_llist *leaf)
{
	t_llist *new_leaf_node;

	new_leaf_node = leaf_node_dup(leaf);
	if (new_leaf_node == NULL)
		return (NULL);
	return (ast_new(OPERATOR, NULL, new_leaf_node));
}

static t_ntree	*create_filename(t_llist *leaf)
{
	t_token *const	token = get_token(leaf->content);
	char	*filename;
	t_llist	*new_leaf_node;

	filename = ft_strdup(token->data);
	if (filename == NULL)
		return (NULL);
	new_leaf_node = leaf_node_dup(leaf);
	if (new_leaf_node == NULL)
		return (free(filename), NULL);
	return (ast_new(FILENAME, filename, new_leaf_node));
}

t_ntree	*create_classic_redirection(t_llist *begin, t_llist *end)
{
	t_llist	*children;
	t_llist	*child;
	// t_llist	*extract;

	(void)end;
	children = NULL;
	// extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(begin, create_operator);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	// extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(begin->next, create_filename);
	if (child == NULL)
		return (llstclear(&children, ast_free), NULL);
	llstadd_back(&children, child);
	return (ast_new(REDIRECTION, NULL, children));
}
