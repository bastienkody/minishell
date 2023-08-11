/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:08:53 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/11 14:31:05 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_ast(t_minishell *minishell)
{
	const t_execute_ast_fun	execute_function = get_execute_function(minishell->ast);

	return (execute_function(minishell, minishell->ast));
}

int	execute_complete_command(t_minishell *minishell, t_ntree *ast)
{
	t_ntree *const			child = ast->children->content;
	const t_execute_ast_fun	execute_function = get_execute_function(child);

	return (execute_function(minishell, child));
}

int	execute_pipeline(t_minishell *minishell, t_ntree *ast)
{
	t_info *const	pipex_info = get_token(ast)->data;

	return (pipex(minishell, pipex_info));
}

// int	execute_compound_command(t_ntree *ast)
// {
// 	t_ntree *const			child = ast->children->content;
// 	const t_execute_ast_fun	execute_function = get_execute_function(child);

// 	return (execute_function(child));
// }

int	execute_logical_expression(t_minishell *minishell, t_ntree *ast)
{
	t_ntree *const			lhs = ast->children->content;
	t_ntree *const			rhs = ast->children->next->content;
	const t_execute_ast_fun	lhs_execute_function = get_execute_function(lhs);
	const t_execute_ast_fun	rhs_execute_function = get_execute_function(rhs);
	int						lhs_return_status;

	lhs_return_status = lhs_execute_function(minishell, lhs);
	if (lhs_return_status == 0 && (intptr_t)get_token(ast)->data == AND)
		return (rhs_execute_function(minishell, rhs));
	else if (lhs_return_status != 0 && (intptr_t)get_token(ast)->data == OR)
		return (rhs_execute_function(minishell, rhs));
	return (lhs_return_status);
}
