/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complete_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:21:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 11:55:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*get_corresponding_parenthesis(t_llist *pos, t_llist *end)
{
	t_llist *current;
	t_token	*current_token;
	int	parenthesis_lvl;

	parenthesis_lvl = 0;
	current = pos;
	while (current != NULL && current != end)
	{
		current_token = get_token(current->content);
		if (current_token->type == opening_parenthesis)
			parenthesis_lvl += 1;
		else if (current_token->type == closing_parenthesis)
			parenthesis_lvl -= 1;
		if (parenthesis_lvl == 0 && current_token->type == closing_parenthesis)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	is_range_compound(t_llist *begin, t_llist *end)
{
	t_llist *const	last = llstlast_range(begin, end);

	return (is_node_opening_parenthesis(begin->content) && last == get_corresponding_parenthesis(begin, end));
}

t_ntree	*create_complete_command(t_llist *leaf_list)
{
	t_llist	*child;

	// if (is_node_compound(leaf_list->content) && llstsize(leaf_list) == 1)
	// 	child = create_child(leaf_list, create_compound_command);
	if (is_range_compound(leaf_list, NULL))
		child = create_child_range(leaf_list, NULL, create_compound_command);
	else if (llstfind_if(leaf_list, (t_predicate)is_node_logical_operator))
		child = create_child_range(leaf_list, NULL, create_logical_expression);
	else
		child = create_child_range(leaf_list, NULL, create_pipeline);
	if (child == NULL)
		return (NULL);
	return (ast_new(COMPLETE_COMMAND, NULL, child));
}
