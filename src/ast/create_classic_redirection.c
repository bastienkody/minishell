/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_classic_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:10:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:46:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_operator(t_llist *leaf_node)
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
	return (ast_new(OPERATOR, NULL, new_leaf));
}

static t_ntree	*create_filename(t_llist *leaf_node)
{
	const t_token	*token = leaf_node->content;
	t_ntree			*new_leaf_content;
	t_llist			*new_leaf;
	char			*filename;

	new_leaf_content = leaf_new(token);
	if (new_leaf_content == NULL)
		return (NULL);
	new_leaf = llstnew(new_leaf_content);
	if (new_leaf == NULL)
		return (ast_free(new_leaf_content), NULL);
	filename = ft_strdup(token->data);
	if (filename == NULL)
		return (llstclear(&new_leaf, ast_free), NULL);
	return (ast_new(FILENAME, filename, new_leaf));
}

t_ntree	*create_classic_redirection(t_llist *begin, t_llist *end)
{
	t_llist	*children;
	t_llist	*child;

	(void)end;
	children = NULL;
	child = create_child(begin, create_operator);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	child = create_child(begin->next, create_filename);
	if (child == NULL)
		return (llstclear(&children, ast_free), NULL);
	llstadd_back(&children, child);
	return (ast_new(REDIRECTION, NULL, children));
}
