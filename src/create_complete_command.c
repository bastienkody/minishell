/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complete_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:21:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/28 09:25:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*create_complete_command(t_llist *leaf_list)
{
	t_llist	*child;

	if (llstfind_if(leaf_list, (int (*)(void *))is_node_logical_operator))
		child = create_child(leaf_list, create_logical_expression);
	else
		child = create_child(leaf_list, create_pipeline);
	if (child == NULL)
		return (NULL);
	return (new_ast(COMPLETE_COMMAND, NULL, child));
}
