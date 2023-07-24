/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:56:38 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 17:12:06 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_lhs(t_llist *llst)
{
	t_llist	*new;

	if (llstfind_if(llst, (t_predicate)is_node_logical_operator) != NULL)
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

t_ntree	*create_logical_expression(t_llist *leaf_list)
{
	t_llist *const	operator_pos = llstfind_if_reverse(leaf_list,
		(t_predicate)is_node_logical_operator);
	t_llist *const	extract
		= llstextract_range(&leaf_list, operator_pos->next, NULL);
	t_llist			*children;
	t_llist			*new_child;

	children = NULL;
	new_child = create_rhs(extract);
	if (new_child == NULL)
		return (NULL);
	llstadd_back(&children, new_child);
	llstremoveone(&leaf_list, operator_pos, (t_del_fun)ast_free);
	new_child = create_lhs(leaf_list);
	if (new_child == NULL)
		return (llstclear(&children, (t_del_fun)ast_free), NULL);
	llstadd_front(&children, new_child);
	return (ast_new(LOGICAL_EXPRESSION, NULL, children));
}
