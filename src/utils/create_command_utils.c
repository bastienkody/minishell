/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 16:55:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_cmd_name(t_llist *leaf_node)
{
	t_llist	*new_leaf_node;

	new_leaf_node = leaf_node_dup(leaf_node);
	if (new_leaf_node == NULL)
		return (NULL);
	return (ast_new(CMD_NAME, NULL, new_leaf_node));
}

t_llist	*find_cmd_name(t_llist	*begin, t_llist *end)
{
	t_llist	*current;

	current = begin;
	while (current != NULL || current != end)
	{
		if (is_node_word(current->content))
			return (current);
		current = llstnext(current, 2);
	}
	return (NULL);
}
