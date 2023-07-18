/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:01:57 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/17 13:55:19 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*create_logical_expression(t_llist *leaf_list)
{
	t_llist	*logical_node_pos;
	t_llist	*children;
	t_llist	*new_child;
	t_llist	*extract;

	children = NULL;
	logical_node_pos = llstfind_if_reverse(leaf_list, (int (*)(void *))is_node_logical_operator);
	extract = llstextract_range(&leaf_list, logical_node_pos->next, NULL);
	if (is_node_compound(extract->content))
		new_child = create_child(extract, create_compound_command);
	else
		new_child = create_child(extract, create_pipeline);
	if (new_child == NULL)
		return (NULL);
	llstadd_back(&children, new_child);
	llstremoveone(&leaf_list, logical_node_pos, (void (*)(void *))free_ast);
	if (llstfind_if(leaf_list, (int (*)(void *))is_node_logical_operator) != NULL)
		new_child = create_child(leaf_list, create_logical_expression);
	else if (is_node_compound(leaf_list->content))
		new_child = create_child(leaf_list, create_compound_command);
	else
		new_child = create_child(leaf_list, create_pipeline);
	if (new_child == NULL)
		return (llstclear(&children, (void (*)(void *))free_ast), NULL);
	llstadd_front(&children, new_child);
	return (new_ast(LOGICAL_EXPRESSION, NULL, children));
}
