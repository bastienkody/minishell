/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:56:38 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/04 12:44:50 by aguyon           ###   ########.fr       */
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
	if (new == NULL)
		llstclear(&llst, ast_free);
	return (new);
}

t_type	get_logical_expression_type(const char *data)
{
	if (ft_strcmp(data, "&&") == 0)
		return (AND);
	else if (ft_strcmp(data, "||") == 0)
		return (OR);
	else
		return (error);
}

t_ntree	*create_logical_expression(t_llist *leaf_list)
{
	t_llist *const	operator_pos = llstfind_if_reverse(leaf_list,
			(t_predicate)is_node_logical_operator);
	t_llist *const	extract
		= llstextract_range(&leaf_list, operator_pos->next, NULL);
	t_llist			*children;
	t_llist			*new_child;
	const t_type	type
		= get_logical_expression_type(get_token(operator_pos->content)->data);

	llstremoveone(&leaf_list, operator_pos, (t_del_fun)ast_free);
	children = NULL;
	new_child = create_rhs(extract);
	if (new_child == NULL)
		return (llstclear(&leaf_list, ast_free), NULL);
	llstadd_back(&children, new_child);
	new_child = create_lhs(leaf_list);
	if (new_child == NULL)
		return (llstclear(&children, ast_free), NULL);
	llstadd_front(&children, new_child);
	return (ast_new(LOGICAL_EXPRESSION, (void *)type, children));
}
