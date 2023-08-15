/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_expression.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:56:38 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 11:53:29 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_lhs(t_llist *begin, t_llist *end)
{
	t_llist	*new;

	if (is_range_compound(begin, end))
		new = create_child_range(begin, end, create_compound_command);
	else if (llstfind_if_range(begin, end, \
		(t_predicate)is_node_logical_operator) != NULL)
		new = create_child_range(begin, end, create_logical_expression);
	else
		new = create_child_range(begin, end, create_pipeline);
	return (new);
}

t_llist	*create_rhs(t_llist *begin, t_llist *end)
{
	t_llist	*new;

	if (is_range_compound(begin, end))
		new = create_child_range(begin, end, create_compound_command);
	else
		new = create_child_range(begin, end, create_pipeline);
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

t_llist	*get_operator_pos(t_llist *rbegin, t_llist *rend)
{
	t_llist	*current;
	t_token	*current_token;
	int		parenthesis_lvl;

	parenthesis_lvl = 0;
	current = rbegin;
	while (current != NULL && current != rend)
	{
		current_token = get_token(current->content);
		if (current_token->type == closing_parenthesis)
			parenthesis_lvl += 1;
		else if (current_token->type == opening_parenthesis)
			parenthesis_lvl -= 1;
		if (parenthesis_lvl == 0 && is_node_logical_operator(current->content))
			return (current);
		current = current->prev;
	}
	return (NULL);
}

t_ntree	*create_logical_expression(t_llist *begin, t_llist *end)
{
	t_llist *const	operator_pos = get_operator_pos(llstlast_range(begin, end), \
		begin->prev);
	t_llist			*children;
	t_llist			*new_child;
	const t_type	type
		= get_logical_expression_type(get_token(operator_pos->content)->data);
	t_ntree			*ast;

	children = NULL;
	new_child = create_rhs(operator_pos->next, end);
	if (new_child == NULL)
		return (NULL);
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
