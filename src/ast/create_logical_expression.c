/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:56:38 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 18:03:41 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_lhs(t_llist *begin, t_llist *end)
{
	t_llist	*new;

	if (llstfind_if_range(begin, end, (t_predicate)is_node_logical_operator) != NULL)
		new = create_child_range(begin, end, create_logical_expression);
	else if (is_node_compound(begin->content))
		new = create_child(begin, create_compound_command);
	else
		new = create_child_range(begin, end, create_pipeline);
	return (new);
}

t_llist	*create_rhs(t_llist *begin, t_llist *end)
{
	t_llist	*new;

	if (is_node_compound(begin->content))
		new = create_child(begin, create_compound_command);
	else
		new = create_child_range(begin, end, create_pipeline);
	// if (new == NULL)
	// 	return (NULL);
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

t_ntree	*create_logical_expression(t_llist *begin, t_llist *end)
{
	t_llist *const	operator_pos = llstfind_if_reverse_range(begin->prev, llstlast(begin),
			(t_predicate)is_node_logical_operator);
	// t_llist *const	extract
	// 	= llstextract_range(&leaf_list, operator_pos->next, NULL);
	t_llist			*children;
	t_llist			*new_child;
	const t_type	type
		= get_logical_expression_type(get_token(operator_pos->content)->data);
	t_ntree	*ast;

	// llstremoveone(&leaf_list, operator_pos, (t_del_fun)ast_free);
	children = NULL;
	new_child = create_rhs(operator_pos->next, end);
	if (new_child == NULL)
		return (NULL);//return (llstclear(&leaf_list, ast_free), NULL);
	llstadd_back(&children, new_child);
	new_child = create_lhs(begin, operator_pos);
	if (new_child == NULL)
		return (llstclear(&children, ast_free), NULL);
	llstadd_front(&children, new_child);
	ast = ast_new(LOGICAL_EXPRESSION, (void *)type, children);
	if (ast == NULL)
		return (llstclear(&children, ast_free), NULL);
	return (ast);
}
