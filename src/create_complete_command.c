/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complete_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:21:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 16:46:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_leaf_logical_expression(t_ast	*ast)
{
	const t_type type = ast->type;

	return (type == and || type == or);
}

t_ast	*create_complete_command(t_llist *leaf_list)
{
	t_llist	*child;

	if (llstfind_if(leaf_list, (int (*)(void *))is_leaf_logical_expression))
		child = create_child(leaf_list, create_logical_expression);
	else
		child = create_child(leaf_list, create_pipeline);
	if (child == NULL)
		return (NULL);
	return (new_ast(COMPLETE_COMMAND, NULL, child));
}
