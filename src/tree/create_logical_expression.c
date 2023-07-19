/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:01:57 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/19 11:26:38 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_lhs(t_llist *llst)
{
	t_llist	*new;

	if (llstfind_if(llst, (int (*)(void *))is_node_logical_operator) != NULL)
		new = create_child(llst, create_logical_expression);
	else if (is_node_compound(llst->content))
		new = create_child(llst, create_compound_command);
	else
		new = create_child(llst, create_pipeline);
	return (new);
}

t_llist	*create_rhs(t_llist *llst)
{
	t_llist	*new;

	if (is_node_compound(llst->content))
		new = create_child(llst, create_compound_command);
	else
		new = create_child(llst, create_pipeline);
	return (new);
}

t_ast	*create_logical_expression(t_llist *leaf_list)
{
	t_llist *const	operator_pos
		= llstfind_if_reverse(leaf_list,
			(int (*)(void *))is_node_logical_operator);
	t_llist *const	extract
		= llstextract_range(&leaf_list, operator_pos->next, NULL);
	t_llist			*children;
	t_llist			*new_child;

	children = NULL;
	new_child = create_rhs(extract);
	if (new_child == NULL)
		return (NULL);
	llstadd_back(&children, new_child);
	llstremoveone(&leaf_list, operator_pos, (void (*)(void *))free_ast);
	new_child = create_lhs(leaf_list);
	if (new_child == NULL)
		return (llstclear(&children, (void (*)(void *))free_ast), NULL);
	llstadd_front(&children, new_child);
	return (new_ast(LOGICAL_EXPRESSION, NULL, children));
}
