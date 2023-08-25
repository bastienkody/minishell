/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complete_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:21:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/25 12:53:58 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*get_corresponding_parenthesis(t_llist *pos, t_llist *end)
{
	t_llist	*current;
	t_type	current_type;
	int		parenthesis_lvl;

	parenthesis_lvl = 0;
	current = pos;
	while (current != NULL && current != end)
	{
		current_type = llst_token_get_type(current);
		if (current_type == opening_parenthesis)
			parenthesis_lvl += 1;
		else if (current_type == closing_parenthesis)
			parenthesis_lvl -= 1;
		if (parenthesis_lvl == 0 && current_type == closing_parenthesis)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	is_range_compound(t_llist *begin, t_llist *end)
{
	t_llist *const	last = llstlast_range(begin, end);

	return (is_token_opening_parenthesis(begin->content) \
		&& last == get_corresponding_parenthesis(begin, end));
}

t_ntree	*create_complete_command(t_llist *leaf_list)
{
	t_llist	*child;

	if (is_range_compound(leaf_list, NULL))
		child = create_child_range(leaf_list, llstlast(leaf_list), create_compound_command);
	else if (llstfind_if(leaf_list, (t_predicate)is_token_logical_operator))
		child = create_child_range(leaf_list, llstlast(leaf_list), create_logical_expression);
	else
		child = create_child_range(leaf_list, llstlast(leaf_list), create_pipeline);
	if (child == NULL)
		return (NULL);
	return (ast_new(COMPLETE_COMMAND, NULL, child));
}
