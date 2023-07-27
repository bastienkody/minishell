/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 11:39:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_operator(t_llist *leaf)
{
	// const t_type	type = get_token(leaf->content)->type;

	return (ast_new(OPERATOR, NULL, leaf));
}

static t_ntree	*create_filename(t_llist *leaf)
{
	t_token *const	token = get_token(leaf->content);
	char *const		filename = ft_strdup(token->data);

	if (filename == NULL)
		return (NULL);
	return (ast_new(FILENAME, filename, leaf));
}

static t_ntree	*create_here_end(t_llist *leaf)
{
	t_token *const	token = get_token(leaf->content);
	char *const		here_end = ft_strdup(token->data);

	if (here_end == NULL)
		return (NULL);
	return (ast_new(HERE_END, here_end, leaf));
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

t_ntree	*create_here_doc(t_llist *leaf_list)
{
	t_llist	*children;
	t_llist	*child;
	t_llist	*extract;

	llstremoveone(&leaf_list, leaf_list, (t_del_fun)ast_free);
	children = NULL;
	extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(extract, create_here_end);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	return (ast_new(HERE_DOC, NULL, children));
}

t_ntree	*create_redirection(t_llist	*leaf_list)
{
	t_ntree *const	operator_leaf = leaf_list->content;
	char	*const	operator_str = get_token(operator_leaf)->data;

	if (ft_strcmp(operator_str, "<<") == 0)
		return (create_here_doc(leaf_list));
	return (create_classic_redirection(leaf_list));
}
