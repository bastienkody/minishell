/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:55:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 14:55:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*get_execute_function(t_ntree *ast)
{
	const t_type	type = get_token(ast)->type;

	if (type == PIPELINE)
		return (execute_pipeline);
	else if (type == COMPLETE_COMMAND)
		return (execute_complete_command);
	else if (type == COMPOUND_COMMAND)
		return (execute_compound_command);
	else if (type == LOGICAL_EXPRESSION)
		return (execute_logical_expression);
	else
		return (NULL);
}
