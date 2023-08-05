/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_classic_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:10:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/05 16:53:08 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_operator(t_llist *leaf_node)
{
	t_llist *new_leaf_node;

	new_leaf_node = leaf_node_dup(leaf_node);
	if (new_leaf_node == NULL)
		return (NULL);
	return (ast_new(OPERATOR, NULL, new_leaf_node));
}

static t_ntree	*create_filename(t_llist *leaf_node)
{
	t_token *const	token = get_token(leaf_node->content);
	char	*filename;
	t_llist	*new_leaf_node;

	filename = ft_strdup(token->data);
	if (filename == NULL)
		return (NULL);
	new_leaf_node = leaf_node_dup(leaf_node);
	if (new_leaf_node == NULL)
		return (free(filename), NULL);
	return (ast_new(FILENAME, filename, new_leaf_node));
}

t_ntree	*create_classic_redirection(t_llist *leaf_list)
{
	t_llist	*children;
	t_llist	*child;
	t_llist	*extract;

	children = NULL;
	extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(extract, create_operator);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(extract, create_filename);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	return (ast_new(REDIRECTION, NULL, children));
}
