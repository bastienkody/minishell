/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:45:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 16:09:14 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_cmd_name(t_llist *leaf)
{
	return (ast_new(CMD_NAME, NULL, leaf));
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
