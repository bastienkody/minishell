/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 16:10:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_operator(t_llist *leaf)
{
	t_type type;

	type = ((t_ast *)leaf->content)->type;
	return (ast_new(OPERATOR, (void *)type, leaf));
}

static t_ntree	*create_filename(t_llist *leaf)
{
	char *const filename = ft_strdup(((t_ast *)leaf->content)->data);

	if (filename == NULL)
		return (NULL);
	return (ast_new(FILENAME, filename, leaf));
}

t_ntree	*create_redirection(t_llist	*leaf_list)
{
	t_llist	*children;
	t_llist	*child;
	t_llist	*extract;

	// if (llstsize(leaf_list) != 2)
	// 	return (NULL);
	// if (!is_node_redirection(leaf_list->content)
	// 	|| !is_node_word(leaf_list->next->content))
	// 	return (NULL);
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