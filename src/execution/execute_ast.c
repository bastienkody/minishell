/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:58:45 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:15:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_ast(t_ntree *ast)
{
	const t_execute_ast_fun	execute_function = get_execute_function(ast);

	return (execute_function(ast));
}

int	execute_complete_command(t_ntree *ast)
{
	t_ntree *const			child = ast->children->content;
	const t_execute_ast_fun	execute_function = get_execute_function(child);

	return (execute_function(child));
}

int	execute_pipeline(t_ntree *ast)
{
	t_info *const	pipex_info = get_token(ast)->data;

	return (pipex(pipex_info));
}

int	execute_compound_command(t_ntree *ast)
{
	t_ntree *const			child = ast->children->content;
	const t_execute_ast_fun	execute_function = get_execute_function(child);

	return (execute_function(child));
}

int	execute_logical_expression(t_ntree *ast)
{
	t_ntree *const			lhs = ast->children->content;
	t_ntree *const			rhs = ast->children->next->content;
	const t_execute_ast_fun	lhs_execute_function = get_execute_function(lhs);
	const t_execute_ast_fun	rhs_execute_function = get_execute_function(rhs);
	int						lhs_return_status;

	lhs_return_status = lhs_execute_function(lhs);
	if (lhs_return_status == 0 && (intptr_t)get_token(ast)->data == AND)
		return (rhs_execute_function(rhs));
	else if (lhs_return_status != 0 && (intptr_t)get_token(ast)->data == OR)
		return (rhs_execute_function(rhs));
	return (lhs_return_status);
}
