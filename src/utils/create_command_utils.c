/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/05 16:54:04 by aguyon           ###   ########.fr       */
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

t_llist	*find_cmd_name(t_llist	*leaf_list)
{
	while (leaf_list != NULL)
	{
		if (is_node_word(leaf_list->content))
			return (leaf_list);
		leaf_list = llstnext(leaf_list, 2);
	}
	return (NULL);
}
