/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:24:08 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 19:25:42 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ast	*create_operator(t_llist *leaf)
{
	return (new_ast(OPERATOR, NULL, leaf));
}

static t_ast	*create_filename(t_llist *leaf)
{
	return (new_ast(FILENAME, NULL, leaf));
}

t_ast	*create_redirection(t_llist	*leaf_list)
{
	t_llist	*children;
	t_llist	*child;
	t_llist	*extract;

	if (llstsize(leaf_list) != 2)
		return (NULL);
	if (!is_node_redirection(leaf_list->content)
		|| !is_node_word(leaf_list->next->content))
		return (NULL);
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
	return (new_ast(REDIRECTION, NULL, children));
}
