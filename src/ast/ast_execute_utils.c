/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execute_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:08:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/11 14:17:14 by aguyon           ###   ########.fr       */
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
	else if (type == LOGICAL_EXPRESSION)
		return (execute_logical_expression);
	else
		return (NULL);
}
