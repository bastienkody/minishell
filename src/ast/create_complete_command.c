/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complete_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:21:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:04:08 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_complete_command(t_llist *leaf_list)
{
	t_llist	*child;

	if (is_node_compound(leaf_list->content) && llstsize(leaf_list) == 1)
		child = create_child(leaf_list, create_compound_command);
	else if (llstfind_if(leaf_list, (t_predicate)is_node_logical_operator))
		child = create_child(leaf_list, create_logical_expression);
	else
		child = create_child(leaf_list, create_pipeline);
	if (child == NULL)
		return (NULL);
	return (ast_new(COMPLETE_COMMAND, NULL, child));
}
