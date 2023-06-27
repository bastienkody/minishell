/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:01:57 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 16:37:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_node_logical(t_ast	*leaf)
{
	const t_type	type = leaf->type;

	return (type == or || type == and);
}

t_ast	*create_logical_expression(t_llist *leaf_list)
{
	t_llist	*logical_node_pos;
	t_llist	*children;
	t_llist	*new_child;

	children = NULL;
	logical_node_pos = llstfind_if(leaf_list, (int (*)(void *))is_node_logical);
	if (logical_node_pos->next == NULL)
		return (NULL);
	new_child = create_child(llstextract_range(&leaf_list, logical_node_pos->next, NULL), create_pipeline);
	if (new_child == NULL)
		return (NULL);
	llstadd_back(&children, new_child);
	llstremoveone(&leaf_list,logical_node_pos ,free);
	if (llstfind_if(leaf_list, (int (*)(void *))is_node_logical) != NULL)
		new_child = create_child(leaf_list, create_logical_expression);
	else
		new_child = create_child(leaf_list, create_pipeline);
	if (new_child == NULL)
		return (NULL);
	llstadd_front(&children, new_child);
	return (new_ast(LOGICAL_EXPRESSION, NULL, children));
}
